/** @file ipc_string_define.h
  * @brief ����Render������Browser����ͨ�����ó���
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2016/7/19
*/
#pragma once

namespace nim_comp
{
	static const char kFocusedNodeChangedMessage[]	= "FocusedNodeChanged";		// webҳ���л�ȡ�����Ԫ�ظı�
	static const char kExecuteCppCallbackMessage[]	= "ExecuteCppCallback";		// ִ�� C++ ����Ϣ�ص�����
	static const char kCallCppFunctionMessage[]		= "CallCppFunction";		// web����C++�ӿڽӿڵ�֪ͨ
	static const char kExecuteJsCallbackMessage[]	= "ExecuteJsCallback";		// web����C++�ӿڽӿڵ�֪ͨ
	static const char kCallJsFunctionMessage[]		= "CallJsFunction";			// C++ ���� JavaScript ֪ͨ
}
