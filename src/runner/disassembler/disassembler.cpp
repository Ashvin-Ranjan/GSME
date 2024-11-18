#include "../runner.h"
#include "../../chunk_handler/chunk_handler.h"

using namespace GMSEDisassembler;

InstructionIdentifier byte_to_ident(u_int8_t byte) {
    return (InstructionIdentifier)byte;
}

std::string ident_to_str(InstructionIdentifier ident) {
    switch (ident) {
        case Convert: return std::string("conv");
        case Multiply: return std::string("mul");
        case Divide: return std::string("div");
        case Remainder: return std::string("rem");
        case Modulo: return std::string("mod");
        case Add: return std::string("add");
        case Subtract: return std::string("sub");
        case And: return std::string("and");
        case Or: return std::string("or");
        case Xor: return std::string("xor");
        case Negative: return std::string("neg");
        case Not: return std::string("not");
        case ShiftLeft: return std::string("shl");
        case ShiftRight: return std::string("shr");
        case Compare: return std::string("cmp");
        case Pop: return std::string("pop");
        case Duplicate: return std::string("dup");
        case Return: return std::string("ret");
        case Exit: return std::string("exit");
        case Popz: return std::string("popz");
        case Branch: return std::string("b");
        case BranchTrue: return std::string("bt");
        case BranchFalse: return std::string("bf");
        case PushEnvironment: return std::string("pushenv");
        case PopEnvironment: return std::string("popenv");
        case Push: return std::string("push");
        case PushLocation: return std::string("pushloc");
        case PushGlobal: return std::string("pushglb");
        case PushBuiltin: return std::string("pushbltn");
        case PushInt: return std::string("pushi");
        case Call: return std::string("call");
        case CallV: return std::string("callv");
        case Break: return std::string("break");
    }
}