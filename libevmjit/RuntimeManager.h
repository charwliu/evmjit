#pragma once

#include "CompilerHelper.h"
#include "Type.h"
#include "RuntimeData.h"
#include "Instruction.h"

namespace dev
{
namespace eth
{
namespace jit
{

class RuntimeManager: public CompilerHelper
{
public:
	RuntimeManager(llvm::IRBuilder<>& _builder);

	llvm::Value* getRuntimePtr();
	llvm::Value* getDataPtr();
	llvm::Value* getEnv();

	llvm::Value* get(RuntimeData::Index _index);
	llvm::Value* get(Instruction _inst);
	llvm::Value* getGas();	// TODO: Remove
	llvm::Value* getCallData();
	llvm::Value* getCode();
	void setGas(llvm::Value* _gas);

	void registerReturnData(llvm::Value* _index, llvm::Value* _size);

	void raiseException(ReturnCode _returnCode);

	static llvm::StructType* getRuntimeType();
	static llvm::StructType* getRuntimeDataType();

private:
	llvm::Value* getPtr(RuntimeData::Index _index);
	void set(RuntimeData::Index _index, llvm::Value* _value);
	llvm::Value* getJmpBuf();

	llvm::GlobalVariable* m_rtPtr = nullptr;
	llvm::GlobalVariable* m_dataPtr = nullptr;
	llvm::Function* m_longjmp = nullptr;
	llvm::Value* m_env = nullptr;
};

}
}
}