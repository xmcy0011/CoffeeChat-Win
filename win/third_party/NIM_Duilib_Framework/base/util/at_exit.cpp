﻿// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Ported by wrt(guangguang)
// Date: 2013/09/17

#include "base/util/at_exit.h"

#include <stddef.h>
#include <ostream>

//#include "base/log/log.h"

namespace nbase
{

// Keep a stack of registered AtExitManagers.  We always operate on the most
// recent, and we should never have more than one outside of testing (for a
// statically linked version of this library).  Testing may use the shadow
// version of the constructor, and if we are building a dynamic library we may
// end up with multiple AtExitManagers on the same process.  We don't protect
// this for thread-safe access, since it will only be modified in testing.
static AtExitManager* g_top_manager = NULL;

AtExitManager::AtExitManager() : next_manager_(g_top_manager)
{
// If multiple modules instantiate AtExitManagers they'll end up living in this
// module... they have to coexist.
#if !defined(COMPONENT_BUILD)
	//DCHECK(!g_top_manager);
#endif
	g_top_manager = this;
}

AtExitManager::~AtExitManager()
{
	if (!g_top_manager) {
		//LOG_ASS("Tried to ~AtExitManager without an AtExitManager");
		return;
	}
	//DCHECK(this == g_top_manager);

	ProcessCallbacksNow();
	g_top_manager = next_manager_;
}

// static
void AtExitManager::RegisterCallback(AtExitCallbackType func, void* param)
{
	//DCHECK(func);
	RegisterTask(nbase::Bind(func, param));
}

// static
void AtExitManager::RegisterTask(StdClosure task)
{
	if (!g_top_manager)
	{
		//LOG_ASS("Tried to RegisterCallback without an AtExitManager");
		return;
	}

	NAutoLock lock(&g_top_manager->lock_);
	g_top_manager->stack_.push(task);
}

// static
void AtExitManager::ProcessCallbacksNow()
{
	if (!g_top_manager)
	{
		//LOG_ASS("Tried to ProcessCallbacksNow without an AtExitManager");
		return;
	}

	NAutoLock lock(&g_top_manager->lock_);

	while (!g_top_manager->stack_.empty())
	{
		StdClosure task = g_top_manager->stack_.top();
		task();
		g_top_manager->stack_.pop();
	}
}

AtExitManager::AtExitManager(bool shadow) : next_manager_(g_top_manager)
{
	//DCHECK(shadow || !g_top_manager);
	g_top_manager = this;
}

}  // namespace nbase
