# port-macros

# port-macros

PM_WritePort(port, value)
PM_DirPort(port, value)
PM_ReadPort(port, var)
PM_SetBitsPort(port, value)
PM_ClearBitsPort(port, value)

BM_Bit(bit)
BM_SetBit(var, bit)
BM_ClearBit(var, bit)
BM_InvBit(var, bit)
BM_TestBit(var, bit)
BM_BitIsClear(var, bit)
BM_BitIsSet(var, bit)
BM_SetBitVal(var, bit, val)

PM_Pin(x)
PM_SetPin(x)
PM_ClearPin(x)
PM_InvPin(x)
PM_TestPin(x)
PM_PinIsSet(x)
PM_PinIsClear(x)
PM_OnPin(x)
PM_OffPin(x)
PM_DirPin(x, y)
