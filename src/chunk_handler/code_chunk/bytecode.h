#ifndef GMSE_BYTECODE_H
#define GMSE_BYTECODE_H

// Details taken from https://web.archive.org/web/20191126144953if_/https://github.com/donkeybonks/acolyte/wiki/Bytecode

#include <stdint.h>
#include <string>
#include <unordered_map>

namespace GMSEDisassembler {
    enum SizeIdentifier {
        Double = (u_int8_t)0x00,
        Float = (u_int8_t)0x01,
        Int = (u_int8_t)0x02,
        Long = (u_int8_t)0x03,
        Bool = (u_int8_t)0x04,
        Variable = (u_int8_t)0x05,
        String = (u_int8_t)0x06,
        Instance = (u_int8_t)0x07,
        Error = (u_int8_t)0x0F,
    };

    // The value of the enum is equal to the size of the instruction
    enum InstructionIdentifier {
        Convert = 2, // conv type, type
        Multiply = 2, // mul type, type
        Divide = 2, // div type, type
        Remainder = 2, // rem, type, type
        Modulo = 2, // mod type, type
        Add = 2, // add type, type
        Subtract = 2, // sub type, type
        And = 2, // and type, type
        Or = 2, // or type, type
        Xor = 2, // xor type, type
        Not = 2, // not type, type
        ArithmeticShiftLeft = 2, // sal type, type
        ArithmeticShiftRight = 2, // sar type, type
        LessThan = 2, // slt type, type
        LessThanEqual = 2, // sle type, type
        Equal = 2, // seq, type, type
        NotEqual = 2, // sne type, type
        GreaterThanEqual = 2, // sge type, type
        GreaterThan = 2, // sgt type, type
        Pop = 8, // pop dest, source, instance, [TODO], Metadata
        Duplicate = 4, // dup type, double (TODO: Check if this is right)
        Return = 2, // ret type
        Exit = 2, // exit type (Should only be exit.i)
        Popz = 2, // popz type
        Branch = 4, // b location
        BranchTrue = 4, // bt location
        BranchFalse = 4, // bf location
        PushEnvironment = 4, // pushenv location
        PopEnvironment = 4, // popenv location
        Push = 2, // Push can vary based on type (TODO: handle this)
        Call = 8, // call type, arguments, function
        Break = 4, // exit type, check
        Invalid = 0, // This is when an invalid byte is encountered
    };

    InstructionIdentifier byte_to_ident(u_int8_t byte);

    int instruction_size(InstructionIdentifier instr);

    std::string instr_to_str(u_int8_t* instr);
}

struct ByteCode {
    u_int8_t* data;
    u_int32_t length;
};

extern std::unordered_map<u_int32_t, ByteCode> bytecode_map;

void free_bytecode_data();

void load_bytecode(u_int32_t offset, u_int32_t length);

#endif