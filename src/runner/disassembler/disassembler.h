#ifndef GMSE_DISASSEMBLER_H
#define GMSE_DISASSEMBLER_H

#include <string>

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
        Convert         = 0x07, // conv type, type
        Multiply        = 0x08, // mul type, type
        Divide          = 0x09, // div type, type
        Remainder       = 0x0A, // rem, type, type
        Modulo          = 0x0B, // mod type, type
        Add             = 0x0C, // add type, type
        Subtract        = 0x0D, // sub type, type
        And             = 0x0E, // and type, type
        Or              = 0x0F, // or type, type
        Xor             = 0x10, // xor type, type
        Negative        = 0x11, // not type, type
        Not             = 0x12, // not type, type
        ShiftLeft       = 0x13, // sal type, type
        ShiftRight      = 0x14, // sar type, type
        Compare         = 0x15, // cmp (TODO: Figure this out)
        Pop             = 0x45, // pop dest, source, instance, [TODO], Metadata
        Duplicate       = 0x86, // dup type, double (TODO: Check if this is right)
        Return          = 0x9C, // ret type
        Exit            = 0x9D, // exit type (Should only be exit.i)
        Popz            = 0x9E, // popz type
        Branch          = 0xB6, // b location
        BranchTrue      = 0xB7, // bt location
        BranchFalse     = 0xB8, // bf location
        PushEnvironment = 0xBA, // pushenv location
        PopEnvironment  = 0xBB, // popenv location
        Push            = 0xC0, // Push can vary based on type (TODO: handle this)
        PushLocation    = 0xC1, // TODO: figure this out
        PushGlobal      = 0xC2, // TODO: figure this out
        PushBuiltin     = 0xC3, // TODO: figure this out
        PushInt         = 0x84, // TODO: figure this out
        Call            = 0xD9, // call type, arguments, function
        CallV           = 0x99, // TODO: Figure this out
        Break           = 0xFF, // exit type, check
    };

    InstructionIdentifier byte_to_ident(u_int8_t byte);

    int instruction_size(InstructionIdentifier instr);

    std::string ident_to_str(InstructionIdentifier ident);

    std::string instr_to_str(u_int8_t* instr);
}

#endif