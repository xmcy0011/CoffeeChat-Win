set DST_DIR=..\src\chatkit\cim\pb\

protoc --cpp_out=%DST_DIR% CIM.Def.proto
protoc --cpp_out=%DST_DIR% CIM.Friend.proto
protoc --cpp_out=%DST_DIR% CIM.Group.proto
protoc --cpp_out=%DST_DIR% CIM.List.proto
protoc --cpp_out=%DST_DIR% CIM.Login.proto
protoc --cpp_out=%DST_DIR% CIM.Message.proto
protoc --cpp_out=%DST_DIR% CIM.Voip.proto