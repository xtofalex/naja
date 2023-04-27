import snl

def constructIBUF(lib):
  ibuf = snl.SNLDesign.createPrimitive(lib, "IBUF")
  i = snl.SNLScalarTerm.create(ibuf, snl.SNLTerm.Direction.Input, "I")
  o = snl.SNLScalarTerm.create(ibuf, snl.SNLTerm.Direction.Output, "O")

def constructOBUF(lib):
  obuf = snl.SNLDesign.createPrimitive(lib, "OBUF")
  i = snl.SNLScalarTerm.create(obuf, snl.SNLTerm.Direction.Input, "I")
  o = snl.SNLScalarTerm.create(obuf, snl.SNLTerm.Direction.Output, "O")

def constructBUFG(lib):
  bufg = snl.SNLDesign.createPrimitive(lib, "BUFG")
  i = snl.SNLScalarTerm.create(bufg, snl.SNLTerm.Direction.Input, "I")
  o = snl.SNLScalarTerm.create(bufg, snl.SNLTerm.Direction.Output, "O")

def constructINV(lib):
  inv = snl.SNLDesign.createPrimitive(lib, "INV")
  i = snl.SNLScalarTerm.create(inv, snl.SNLTerm.Direction.Input, "I")
  o = snl.SNLScalarTerm.create(inv, snl.SNLTerm.Direction.Output, "O")

def constructCARRY4(lib):
  carry4 = snl.SNLDesign.createPrimitive(lib, "CARRY4")
  o = snl.SNLBusTerm.create(carry4, snl.SNLTerm.Direction.Output, 3, 0, "O")
  co = snl.SNLBusTerm.create(carry4, snl.SNLTerm.Direction.Output, 3, 0, "CO")
  di = snl.SNLBusTerm.create(carry4, snl.SNLTerm.Direction.Input, 3, 0, "DI")
  s = snl.SNLBusTerm.create(carry4, snl.SNLTerm.Direction.Input, 3, 0, "S")
  cyinit = snl.SNLScalarTerm.create(carry4, snl.SNLTerm.Direction.Input, "CYINIT")
  ci = snl.SNLScalarTerm.create(carry4, snl.SNLTerm.Direction.Input, "CI")

def constructLUT1(lib):
  lut1 = snl.SNLDesign.createPrimitive(lib, "LUT1")
  i0 = snl.SNLScalarTerm.create(lut1, snl.SNLTerm.Direction.Input, "I0")
  o = snl.SNLScalarTerm.create(lut1, snl.SNLTerm.Direction.Output, "O")
  snl.SNLParameter.create_binary(lut1, "INIT", 2, 0b00)

def constructLUT2(lib):
  lut2 = snl.SNLDesign.createPrimitive(lib, "LUT2")
  i0 = snl.SNLScalarTerm.create(lut2, snl.SNLTerm.Direction.Input, "I0")
  i1 = snl.SNLScalarTerm.create(lut2, snl.SNLTerm.Direction.Input, "I1")
  o = snl.SNLScalarTerm.create(lut2, snl.SNLTerm.Direction.Output, "O")
  snl.SNLParameter.create_binary(lut2, "INIT", 4, 0x0)

def constructLUT3(lib):
  lut3 = snl.SNLDesign.createPrimitive(lib, "LUT3")
  i0 = snl.SNLScalarTerm.create(lut3, snl.SNLTerm.Direction.Input, "I0")
  i1 = snl.SNLScalarTerm.create(lut3, snl.SNLTerm.Direction.Input, "I1")
  i2 = snl.SNLScalarTerm.create(lut3, snl.SNLTerm.Direction.Input, "I2")
  o = snl.SNLScalarTerm.create(lut3, snl.SNLTerm.Direction.Output, "O")
  snl.SNLParameter.create_binary(lut3, "INIT", 8, 0x00)

def constructLUT4(lib):
  lut4 = snl.SNLDesign.createPrimitive(lib, "LUT4")
  i0 = snl.SNLScalarTerm.create(lut4, snl.SNLTerm.Direction.Input, "I0")
  i1 = snl.SNLScalarTerm.create(lut4, snl.SNLTerm.Direction.Input, "I1")
  i2 = snl.SNLScalarTerm.create(lut4, snl.SNLTerm.Direction.Input, "I2")
  i3 = snl.SNLScalarTerm.create(lut4, snl.SNLTerm.Direction.Input, "I3")
  o = snl.SNLScalarTerm.create(lut4, snl.SNLTerm.Direction.Output, "O")
  snl.SNLParameter.create_binary(lut4, "INIT", 16, 0x0000)

def constructLUT5(lib):
  lut5 = snl.SNLDesign.createPrimitive(lib, "LUT5")
  i0 = snl.SNLScalarTerm.create(lut5, snl.SNLTerm.Direction.Input, "I0")
  i1 = snl.SNLScalarTerm.create(lut5, snl.SNLTerm.Direction.Input, "I1")
  i2 = snl.SNLScalarTerm.create(lut5, snl.SNLTerm.Direction.Input, "I2")
  i3 = snl.SNLScalarTerm.create(lut5, snl.SNLTerm.Direction.Input, "I3")
  i4 = snl.SNLScalarTerm.create(lut5, snl.SNLTerm.Direction.Input, "I4")
  o = snl.SNLScalarTerm.create(lut5, snl.SNLTerm.Direction.Output, "O")
  snl.SNLParameter.create_binary(lut5, "INIT", 32, 0x00000000)

def constructLUT6(lib):
  lut6 = snl.SNLDesign.createPrimitive(lib, "LUT6")
  i0 = snl.SNLScalarTerm.create(lut6, snl.SNLTerm.Direction.Input, "I0")
  i1 = snl.SNLScalarTerm.create(lut6, snl.SNLTerm.Direction.Input, "I1")
  i2 = snl.SNLScalarTerm.create(lut6, snl.SNLTerm.Direction.Input, "I2")
  i3 = snl.SNLScalarTerm.create(lut6, snl.SNLTerm.Direction.Input, "I3")
  i4 = snl.SNLScalarTerm.create(lut6, snl.SNLTerm.Direction.Input, "I4")
  i5 = snl.SNLScalarTerm.create(lut6, snl.SNLTerm.Direction.Input, "I5")
  o = snl.SNLScalarTerm.create(lut6, snl.SNLTerm.Direction.Output, "O")
  snl.SNLParameter.create_binary(lut6, "INIT", 64, 0x0000000000000000)

def constructMUXF7(lib):
  muxf7 = snl.SNLDesign.createPrimitive(lib, "MUXF7")
  i0 = snl.SNLScalarTerm.create(muxf7, snl.SNLTerm.Direction.Input, "I0")
  i1 = snl.SNLScalarTerm.create(muxf7, snl.SNLTerm.Direction.Input, "I1")
  o = snl.SNLScalarTerm.create(muxf7, snl.SNLTerm.Direction.Output, "O")
  s = snl.SNLScalarTerm.create(muxf7, snl.SNLTerm.Direction.Input, "S")

def constructMUXF8(lib):
  muxf8 = snl.SNLDesign.createPrimitive(lib, "MUXF8")
  i0 = snl.SNLScalarTerm.create(muxf8, snl.SNLTerm.Direction.Input, "I0")
  i1 = snl.SNLScalarTerm.create(muxf8, snl.SNLTerm.Direction.Input, "I1")
  o = snl.SNLScalarTerm.create(muxf8, snl.SNLTerm.Direction.Output, "O")
  s = snl.SNLScalarTerm.create(muxf8, snl.SNLTerm.Direction.Input, "S")

def constructSRL16E(lib):
  srl16e = snl.SNLDesign.createPrimitive(lib, "SRL16E")
  ce = snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Input, "CE")
  clk = snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Input, "CLK")
  d = snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Input, "D")
  q = snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Output, "Q")
  a0 = snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Input, "A0")
  a1 = snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Input, "A1")
  a2 = snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Input, "A2")
  a3 = snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Input, "A3")
  snl.SNLParameter.create_binary(srl16e, "INIT", 16, 0x0000)
  snl.SNLParameter.create_binary(srl16e, "IS_CLK_INVERTED", 1, 0)

def constructFDRE(lib):
  fdre = snl.SNLDesign.createPrimitive(lib, "FDRE")
  q = snl.SNLScalarTerm.create(fdre, snl.SNLTerm.Direction.Output, "Q")
  c = snl.SNLScalarTerm.create(fdre, snl.SNLTerm.Direction.Input, "C")
  ce = snl.SNLScalarTerm.create(fdre, snl.SNLTerm.Direction.Input, "CE")
  r = snl.SNLScalarTerm.create(fdre, snl.SNLTerm.Direction.Input, "R")
  d = snl.SNLScalarTerm.create(fdre, snl.SNLTerm.Direction.Input, "D")
  snl.SNLParameter.create_binary(fdre, "INIT", 1, 0b0)
  
def constructFDSE(lib):
  fdse = snl.SNLDesign.createPrimitive(lib, "FDSE")
  snl.SNLScalarTerm.create(fdse, snl.SNLTerm.Direction.Output, "Q")
  snl.SNLScalarTerm.create(fdse, snl.SNLTerm.Direction.Input, "C")
  snl.SNLScalarTerm.create(fdse, snl.SNLTerm.Direction.Input, "CE")
  snl.SNLScalarTerm.create(fdse, snl.SNLTerm.Direction.Input, "S")
  snl.SNLScalarTerm.create(fdse, snl.SNLTerm.Direction.Input, "D")
  snl.SNLParameter.create_binary(fdse, "INIT", 1, 0b0)

def constructRAMB18E1(lib):
  ramb18e1 = snl.SNLDesign.createPrimitive(lib, "RAMB18E1")
  snl.SNLBusTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, 13, 0, "ADDRARDADDR")
  snl.SNLBusTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, 13, 0, "ADDRBWRADDR")
  snl.SNLScalarTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, "CLKARDCLK")
  snl.SNLScalarTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, "CLKBWRCLK")
  snl.SNLBusTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, 15, 0, "DIADI")
  snl.SNLBusTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, 15, 0, "DIBDI")
  snl.SNLBusTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, 1, 0, "DIPADIP")
  snl.SNLBusTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, 1, 0, "DIPBDIP")
  snl.SNLBusTerm.create(ramb18e1, snl.SNLTerm.Direction.Output, 15, 0, "DOADO")
  snl.SNLBusTerm.create(ramb18e1, snl.SNLTerm.Direction.Output, 15, 0, "DOBDO")
  snl.SNLBusTerm.create(ramb18e1, snl.SNLTerm.Direction.Output, 1, 0, "DOPADOP")
  snl.SNLBusTerm.create(ramb18e1, snl.SNLTerm.Direction.Output, 1, 0, "DOPBDOP")
  snl.SNLScalarTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, "ENARDEN")
  snl.SNLScalarTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, "ENBWREN")
  snl.SNLScalarTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, "REGCEAREGCE")
  snl.SNLScalarTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, "REGCEB")
  snl.SNLScalarTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, "RSTRAMARSTRAM")
  snl.SNLScalarTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, "RSTRAMB")
  snl.SNLScalarTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, "RSTREGARSTREG")
  snl.SNLScalarTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, "RSTREGB")
  snl.SNLBusTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, 1, 0, "WEA")
  snl.SNLBusTerm.create(ramb18e1, snl.SNLTerm.Direction.Input, 3, 0, "WEBWE")
  snl.SNLParameter.create_decimal(ramb18e1, "DOA_REG", 0)
  snl.SNLParameter.create_decimal(ramb18e1, "DOB_REG", 0)
  snl.SNLParameter.create_binary(ramb18e1, "INIT_A", 18, 0x00000)
  snl.SNLParameter.create_binary(ramb18e1, "INIT_B", 18, 0x00000)
  for i in range(64):
    paramName = "INIT_" + hex(i)[2:].zfill(2).upper()
    snl.SNLParameter.create_binary(ramb18e1, paramName, 256, 0)
  for i in range(8):
    paramName = "INITP_" + hex(i)[2:].zfill(2).upper()
    snl.SNLParameter.create_binary (ramb18e1, paramName, 256, 0)
  snl.SNLParameter.create_string(ramb18e1, "RAM_MODE", "TDP")
  snl.SNLParameter.create_decimal(ramb18e1, "READ_WIDTH_A", 0)
  snl.SNLParameter.create_decimal(ramb18e1, "READ_WIDTH_B", 0)
  snl.SNLParameter.create_binary(ramb18e1, "SRVAL_A", 18, 0)
  snl.SNLParameter.create_binary(ramb18e1, "SRVAL_B", 18, 0)
  snl.SNLParameter.create_string(ramb18e1, "WRITE_MODE_A", "WRITE_FIRST")
  snl.SNLParameter.create_string(ramb18e1, "WRITE_MODE_B", "WRITE_FIRST")
  snl.SNLParameter.create_decimal(ramb18e1, "WRITE_WIDTH_A", 0)
  snl.SNLParameter.create_decimal(ramb18e1, "WRITE_WIDTH_B", 0)
  

def constructRAMB36E1(lib):
  ramb36e1 = snl.SNLDesign.createPrimitive(lib, "RAMB36E1")
  snl.SNLBusTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, 15, 0, "ADDRARDADDR")
  snl.SNLBusTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, 15, 0, "ADDRBWRADDR")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, "CASCADEINA")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, "CASCADEINB")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Output, "CASCADEOUTA")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Output, "CASCADEOUTB")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, "CLKARDCLK")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, "CLKBWRCLK")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Output, "DBITERR")
  snl.SNLBusTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, 31, 0, "DIADI")
  snl.SNLBusTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, 31, 0, "DIBDI")
  snl.SNLBusTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, 3, 0, "DIPADIP")
  snl.SNLBusTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, 3, 0, "DIPBDIP")
  snl.SNLBusTerm.create(ramb36e1, snl.SNLTerm.Direction.Output, 31, 0, "DOADO")
  snl.SNLBusTerm.create(ramb36e1, snl.SNLTerm.Direction.Output, 31, 0, "DOBDO")
  snl.SNLBusTerm.create(ramb36e1, snl.SNLTerm.Direction.Output, 3, 0, "DOPADOP")
  snl.SNLBusTerm.create(ramb36e1, snl.SNLTerm.Direction.Output, 3, 0, "DOPBDOP")
  snl.SNLBusTerm.create(ramb36e1, snl.SNLTerm.Direction.Output, 7, 0, "ECCPARITY")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, "ENARDEN")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, "ENBWREN")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, "INJECTDBITERR")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, "INJECTSBITERR")
  snl.SNLBusTerm.create(ramb36e1, snl.SNLTerm.Direction.Output, 8, 0, "RDADDRECC")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, "REGCEAREGCE")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, "REGCEB")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, "RSTRAMARSTRAM")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, "RSTRAMB")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, "RSTREGARSTREG")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, "RSTREGB")
  snl.SNLScalarTerm.create(ramb36e1, snl.SNLTerm.Direction.Output, "SBITERR")
  snl.SNLBusTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, 3, 0, "WEA")
  snl.SNLBusTerm.create(ramb36e1, snl.SNLTerm.Direction.Input, 7, 0, "WEBWE")

  snl.SNLParameter.create_decimal(ramb36e1, "DOA_REG", 0)
  snl.SNLParameter.create_decimal(ramb36e1, "DOB_REG", 0)
  snl.SNLParameter.create_binary(ramb36e1, "INIT_A", 36, 0)
  snl.SNLParameter.create_binary(ramb36e1, "INIT_B", 36, 0)
  for i in range(128):
    paramName = "INIT_" + hex(i)[2:].zfill(2).upper()
    snl.SNLParameter.create_binary(ramb36e1, paramName, 256, 0)
  for i in range(16):
    paramName = "INITP_" + hex(i)[2:].zfill(2).upper()
    snl.SNLParameter.create_binary(ramb36e1, paramName, 256, 0)
  snl.SNLParameter.create_string(ramb36e1, "RAM_MODE", "TDP")
  snl.SNLParameter.create_decimal(ramb36e1, "READ_WIDTH_A", 0)
  snl.SNLParameter.create_decimal(ramb36e1, "READ_WIDTH_B", 0)
  snl.SNLParameter.create_decimal(ramb36e1, "WRITE_WIDTH_A", 0)
  snl.SNLParameter.create_decimal(ramb36e1, "WRITE_WIDTH_B", 0)
  snl.SNLParameter.create_binary(ramb36e1, "SRVAL_A", 36, 0)
  snl.SNLParameter.create_binary(ramb36e1, "SRVAL_B", 36, 0)
  snl.SNLParameter.create_string(ramb36e1, "WRITE_MODE_A", "WRITE_FIRST")
  snl.SNLParameter.create_string(ramb36e1, "WRITE_MODE_B", "WRITE_FIRST")

def constructPrimitives(lib):
  constructIBUF(lib)
  constructOBUF(lib)
  constructBUFG(lib)
  constructINV(lib)
  constructCARRY4(lib)
  constructLUT1(lib)
  constructLUT2(lib)
  constructLUT3(lib)
  constructLUT4(lib)
  constructLUT5(lib)
  constructLUT6(lib)
  constructMUXF7(lib)
  constructMUXF8(lib)
  constructSRL16E(lib)
  constructFDRE(lib)
  constructFDSE(lib)
  constructRAMB18E1(lib)
  constructRAMB36E1(lib)
