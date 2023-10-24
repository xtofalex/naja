import snl

def constructIBUF(lib):
  ibuf = snl.SNLDesign.createPrimitive(lib, "IBUF")
  i = snl.SNLScalarTerm.create(ibuf, snl.SNLTerm.Direction.Input, "I")
  o = snl.SNLScalarTerm.create(ibuf, snl.SNLTerm.Direction.Output, "O")
  ibuf.addCombinatorialArcs(i, o)

def constructOBUF(lib):
  obuf = snl.SNLDesign.createPrimitive(lib, "OBUF")
  i = snl.SNLScalarTerm.create(obuf, snl.SNLTerm.Direction.Input, "I")
  o = snl.SNLScalarTerm.create(obuf, snl.SNLTerm.Direction.Output, "O")
  obuf.addCombinatorialArcs(i, o)

def constructBUFG(lib):
  bufg = snl.SNLDesign.createPrimitive(lib, "BUFG")
  i = snl.SNLScalarTerm.create(bufg, snl.SNLTerm.Direction.Input, "I")
  o = snl.SNLScalarTerm.create(bufg, snl.SNLTerm.Direction.Output, "O")
  bufg.addCombinatorialArcs(i, o)

def constructDSP48E1(lib):
  dsp48e1 = snl.SNLDesign.createPrimitive(lib, "DSP48E1")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Output, 29, 0, "ACOUT")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Output, 17, 0, "BCOUT")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Output, "CARRYCASCOUT")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "MULTSIGNOUT")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, 47, 0, "PCOUT")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Output, "OVERFLOW")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Output, "PATTERNBDETECT")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Output, "PATTERNDETECT")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Output, "UNDERFLOW")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Output, 3, 0, "CARRYOUT")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Output, 47, 0, "P")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, 29, 0, "ACIN")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, 17, 0, "BCIN")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CARRYCASCIN")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "MULTSIGNIN")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, 47, 0, "PCIN")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, 3, 0, "ALUMODE")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, 2, 0, "CARRYINSEL")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CLK")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, 4, 0, "INMODE")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, 6, 0, "OPMODE")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, 29, 0, "A")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, 17, 0, "B")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, 47, 0, "C")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CARRYIN")
  snl.SNLBusTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, 24, 0, "D")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CEA1")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CEA2")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CEAD")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CEALUMODE")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CEB1")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CEB2")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CEC")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CECARRYIN")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CECTRL")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CED")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CEINMODE")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CEM")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "CEP")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "RSTA")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "RSTALLCARRYIN")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "RSTALUMODE")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "RSTB")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "RSTC")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "RSTCTRL")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "RSTD")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "RSTINMODE")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "RSTM")
  snl.SNLScalarTerm.create(dsp48e1, snl.SNLTerm.Direction.Input, "RSTP")
  snl.SNLParameter.create_decimal(dsp48e1, "ACASCREG", 1)
  snl.SNLParameter.create_decimal(dsp48e1, "ADREG", 1)
  snl.SNLParameter.create_string(dsp48e1, "A_INPUT", "DIRECT")
  snl.SNLParameter.create_decimal(dsp48e1, "ALUMODEREG", 1)
  snl.SNLParameter.create_decimal(dsp48e1, "AREG", 1)
  snl.SNLParameter.create_decimal(dsp48e1, "BCASCREG", 1)
  snl.SNLParameter.create_string(dsp48e1, "B_INPUT", "DIRECT")
  snl.SNLParameter.create_decimal(dsp48e1, "BREG", 1)
  snl.SNLParameter.create_decimal(dsp48e1, "CARRYINREG", 1)
  snl.SNLParameter.create_decimal(dsp48e1, "CARRYINSELREG", 1)
  snl.SNLParameter.create_decimal(dsp48e1, "CREG", 1)
  snl.SNLParameter.create_decimal(dsp48e1, "DREG", 1)
  snl.SNLParameter.create_decimal(dsp48e1, "INMODEREG", 1)
  snl.SNLParameter.create_decimal(dsp48e1, "MREG", 1)
  snl.SNLParameter.create_decimal(dsp48e1, "OPMODEREG", 1)
  snl.SNLParameter.create_decimal(dsp48e1, "PREG", 1)
  snl.SNLParameter.create_boolean(dsp48e1, "USE_DPORT", False)
  snl.SNLParameter.create_string(dsp48e1, "USE_MULT", "MULTIPLY")
  snl.SNLParameter.create_string(dsp48e1, "USE_SIMD", "ONE48")

def constructINV(lib):
  inv = snl.SNLDesign.createPrimitive(lib, "INV")
  i = snl.SNLScalarTerm.create(inv, snl.SNLTerm.Direction.Input, "I")
  o = snl.SNLScalarTerm.create(inv, snl.SNLTerm.Direction.Output, "O")
  snl.SNLDesign.addCombinatorialArcs(i, o)

def constructCARRY4(lib):
  carry4 = snl.SNLDesign.createPrimitive(lib, "CARRY4")
  carry4 = snl.SNLDesign.createPrimitive(lib, "CARRY4")
  o = snl.SNLBusTerm.create(carry4, snl.SNLTerm.Direction.Output, 3, 0, "O")
  co = snl.SNLBusTerm.create(carry4, snl.SNLTerm.Direction.Output, 3, 0, "CO")
  di = snl.SNLBusTerm.create(carry4, snl.SNLTerm.Direction.Input, 3, 0, "DI")
  s = snl.SNLBusTerm.create(carry4, snl.SNLTerm.Direction.Input, 3, 0, "S")
  cyinit  = snl.SNLScalarTerm.create(carry4, snl.SNLTerm.Direction.Input, "CYINIT")
  ci = snl.SNLScalarTerm.create(carry4, snl.SNLTerm.Direction.Input, "CI")
  o_bits = [b for b in o.getBits()]
  co_bits = [b for b in co.getBits()] 
  di_bits = [b for b in di.getBits()] 
  s_bits = [b for b in s.getBits()] 
  #cyinit and ci are in combinatorial dependency with o and co outputs 
  snl.SNLDesign.addCombinatorialArcs([cyinit, ci], [o, co])
  snl.SNLDesign.addCombinatorialArcs(s_bits[0], [o, co])
  snl.SNLDesign.addCombinatorialArcs(s_bits[1], [o_bits[1], o_bits[2], o_bits[3]])
  snl.SNLDesign.addCombinatorialArcs(s_bits[1], [co_bits[1], co_bits[2], co_bits[3]])
  snl.SNLDesign.addCombinatorialArcs(s_bits[2], [o_bits[2], o_bits[3]])
  snl.SNLDesign.addCombinatorialArcs(s_bits[2], [co_bits[2], co_bits[3]])
  snl.SNLDesign.addCombinatorialArcs(s_bits[3], o_bits[3])
  snl.SNLDesign.addCombinatorialArcs(s_bits[3], co_bits[3])
  snl.SNLDesign.addCombinatorialArcs(di_bits[0], [o_bits[1], o_bits[2], o_bits[3]])
  snl.SNLDesign.addCombinatorialArcs(di_bits[0], co)
  snl.SNLDesign.addCombinatorialArcs(di_bits[1], [o_bits[2], o_bits[3]])
  snl.SNLDesign.addCombinatorialArcs(di_bits[1], [co_bits[1], co_bits[2], co_bits[3]])
  snl.SNLDesign.addCombinatorialArcs(di_bits[2], o_bits[3])
  snl.SNLDesign.addCombinatorialArcs(di_bits[2], [co_bits[2], co_bits[3]])
  snl.SNLDesign.addCombinatorialArcs(di_bits[3], co_bits[3])

def constructLUT1(lib):
  lut1 = snl.SNLDesign.createPrimitive(lib, "LUT1")
  i0 = snl.SNLScalarTerm.create(lut1, snl.SNLTerm.Direction.Input, "I0")
  o = snl.SNLScalarTerm.create(lut1, snl.SNLTerm.Direction.Output, "O")
  snl.SNLDesign.addCombinatorialArcs(i0, o)
  snl.SNLParameter.create_binary(lut1, "INIT", 2, 0b00)

def constructLUT2(lib):
  lut2 = snl.SNLDesign.createPrimitive(lib, "LUT2")
  i0 = snl.SNLScalarTerm.create(lut2, snl.SNLTerm.Direction.Input, "I0")
  i1 = snl.SNLScalarTerm.create(lut2, snl.SNLTerm.Direction.Input, "I1")
  o = snl.SNLScalarTerm.create(lut2, snl.SNLTerm.Direction.Output, "O")
  snl.SNLDesign.addCombinatorialArcs([i0, i1], o)
  snl.SNLParameter.create_binary(lut2, "INIT", 4, 0x0)

def constructLUT3(lib):
  lut3 = snl.SNLDesign.createPrimitive(lib, "LUT3")
  i0 = snl.SNLScalarTerm.create(lut3, snl.SNLTerm.Direction.Input, "I0")
  i1 = snl.SNLScalarTerm.create(lut3, snl.SNLTerm.Direction.Input, "I1")
  i2 = snl.SNLScalarTerm.create(lut3, snl.SNLTerm.Direction.Input, "I2")
  o = snl.SNLScalarTerm.create(lut3, snl.SNLTerm.Direction.Output, "O")
  snl.SNLDesign.addCombinatorialArcs([i0, i1, i2], o)
  snl.SNLParameter.create_binary(lut3, "INIT", 8, 0x00)

def constructLUT4(lib):
  lut4 = snl.SNLDesign.createPrimitive(lib, "LUT4")
  i0 = snl.SNLScalarTerm.create(lut4, snl.SNLTerm.Direction.Input, "I0")
  i1 = snl.SNLScalarTerm.create(lut4, snl.SNLTerm.Direction.Input, "I1")
  i2 = snl.SNLScalarTerm.create(lut4, snl.SNLTerm.Direction.Input, "I2")
  i3 = snl.SNLScalarTerm.create(lut4, snl.SNLTerm.Direction.Input, "I3")
  o = snl.SNLScalarTerm.create(lut4, snl.SNLTerm.Direction.Output, "O")
  snl.SNLDesign.addCombinatorialArcs([i0, i1, i2, i3], o)
  snl.SNLParameter.create_binary(lut4, "INIT", 16, 0x0000)

def constructLUT5(lib):
  lut5 = snl.SNLDesign.createPrimitive(lib, "LUT5")
  i0 = snl.SNLScalarTerm.create(lut5, snl.SNLTerm.Direction.Input, "I0")
  i1 = snl.SNLScalarTerm.create(lut5, snl.SNLTerm.Direction.Input, "I1")
  i2 = snl.SNLScalarTerm.create(lut5, snl.SNLTerm.Direction.Input, "I2")
  i3 = snl.SNLScalarTerm.create(lut5, snl.SNLTerm.Direction.Input, "I3")
  i4 = snl.SNLScalarTerm.create(lut5, snl.SNLTerm.Direction.Input, "I4")
  o = snl.SNLScalarTerm.create(lut5, snl.SNLTerm.Direction.Output, "O")
  snl.SNLDesign.addCombinatorialArcs([i0, i1, i2, i3, i4], o)
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
  snl.SNLDesign.addCombinatorialArcs([i0, i1, i2, i3, i4, i5], o)
  snl.SNLParameter.create_binary(lut6, "INIT", 64, 0x0000000000000000)

def constructMUXF7(lib):
  muxf7 = snl.SNLDesign.createPrimitive(lib, "MUXF7")
  i0 = snl.SNLScalarTerm.create(muxf7, snl.SNLTerm.Direction.Input, "I0")
  i1 = snl.SNLScalarTerm.create(muxf7, snl.SNLTerm.Direction.Input, "I1")
  o = snl.SNLScalarTerm.create(muxf7, snl.SNLTerm.Direction.Output, "O")
  s = snl.SNLScalarTerm.create(muxf7, snl.SNLTerm.Direction.Input, "S")
  snl.SNLDesign.addCombinatorialArcs([i0, i1, s], o)

def constructMUXF8(lib):
  muxf8 = snl.SNLDesign.createPrimitive(lib, "MUXF8")
  i0 = snl.SNLScalarTerm.create(muxf8, snl.SNLTerm.Direction.Input, "I0")
  i1 = snl.SNLScalarTerm.create(muxf8, snl.SNLTerm.Direction.Input, "I1")
  o = snl.SNLScalarTerm.create(muxf8, snl.SNLTerm.Direction.Output, "O")
  s = snl.SNLScalarTerm.create(muxf8, snl.SNLTerm.Direction.Input, "S")
  snl.SNLDesign.addCombinatorialArcs([i0, i1, s], o)

def constructSRL16E(lib):
  srl16e = snl.SNLDesign.createPrimitive(lib, "SRL16E")
  snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Input, "CE")
  snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Input, "CLK")
  snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Input, "D")
  snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Output, "Q")
  snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Input, "A0")
  snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Input, "A1")
  snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Input, "A2")
  snl.SNLScalarTerm.create(srl16e, snl.SNLTerm.Direction.Input, "A3")
  snl.SNLParameter.create_binary(srl16e, "INIT", 16, 0x0000)
  snl.SNLParameter.create_binary(srl16e, "IS_CLK_INVERTED", 1, 0)

def constructFDCE(lib):
  fdce = snl.SNLDesign.createPrimitive(lib, "FDCE")
  q = snl.SNLScalarTerm.create(fdce, snl.SNLTerm.Direction.Output, "Q")
  c = snl.SNLScalarTerm.create(fdce, snl.SNLTerm.Direction.Input, "C")
  ce = snl.SNLScalarTerm.create(fdce, snl.SNLTerm.Direction.Input, "CE")
  clr = snl.SNLScalarTerm.create(fdce, snl.SNLTerm.Direction.Input, "CLR")
  d = snl.SNLScalarTerm.create(fdce, snl.SNLTerm.Direction.Input, "D")
  snl.SNLParameter.create_binary(fdce, "INIT", 1, 0b0)
  snl.SNLDesign.addInputsToClockArcs([ce, clr, d], c)
  snl.SNLDesign.addClockToOutputsArcs(c, q)

def constructFDPE(lib):
  fdpe = snl.SNLDesign.createPrimitive(lib, "FDPE")
  q = snl.SNLScalarTerm.create(fdpe, snl.SNLTerm.Direction.Output, "Q")
  c = snl.SNLScalarTerm.create(fdpe, snl.SNLTerm.Direction.Input, "C")
  ce = snl.SNLScalarTerm.create(fdpe, snl.SNLTerm.Direction.Input, "CE")
  pre = snl.SNLScalarTerm.create(fdpe, snl.SNLTerm.Direction.Input, "PRE")
  d = snl.SNLScalarTerm.create(fdpe, snl.SNLTerm.Direction.Input, "D")
  snl.SNLParameter.create_binary(fdpe, "INIT", 1, 0b1)
  snl.SNLDesign.addInputsToClockArcs([ce, pre, d], c)
  snl.SNLDesign.addClockToOutputsArcs(c, q)

def constructFDRE(lib):
  fdre = snl.SNLDesign.createPrimitive(lib, "FDRE")
  q = snl.SNLScalarTerm.create(fdre, snl.SNLTerm.Direction.Output, "Q")
  c = snl.SNLScalarTerm.create(fdre, snl.SNLTerm.Direction.Input, "C")
  ce = snl.SNLScalarTerm.create(fdre, snl.SNLTerm.Direction.Input, "CE")
  q = snl.SNLScalarTerm.create(fdre, snl.SNLTerm.Direction.Input, "R")
  r = snl.SNLScalarTerm.create(fdre, snl.SNLTerm.Direction.Input, "D")
  d = snl.SNLParameter.create_binary(fdre, "INIT", 1, 0b0)
  snl.SNLDesign.addInputsToClockArcs([ce, r, d], c)
  snl.SNLDesign.addClockToOutputsArcs(c, q)

def constructFDSE(lib):
  fdse = snl.SNLDesign.createPrimitive(lib, "FDSE")
  q = snl.SNLScalarTerm.create(fdse, snl.SNLTerm.Direction.Output, "Q")
  c = snl.SNLScalarTerm.create(fdse, snl.SNLTerm.Direction.Input, "C")
  ce = snl.SNLScalarTerm.create(fdse, snl.SNLTerm.Direction.Input, "CE")
  s = snl.SNLScalarTerm.create(fdse, snl.SNLTerm.Direction.Input, "S")
  d = snl.SNLScalarTerm.create(fdse, snl.SNLTerm.Direction.Input, "D")
  snl.SNLParameter.create_binary(fdse, "INIT", 1, 0b0)
  snl.SNLDesign.addInputsToClockArcs([ce, s, d], c)
  snl.SNLDesign.addClockToOutputsArcs(c, q)

def constructRAM32M(lib):
  ram32m = snl.SNLDesign.createPrimitive(lib, "RAM32M")
  snl.SNLBusTerm.create(ram32m, snl.SNLTerm.Direction.Output, 1, 0, "DOA")
  snl.SNLBusTerm.create(ram32m, snl.SNLTerm.Direction.Output, 1, 0, "DOB")
  snl.SNLBusTerm.create(ram32m, snl.SNLTerm.Direction.Output, 1, 0, "DOC")
  snl.SNLBusTerm.create(ram32m, snl.SNLTerm.Direction.Output, 1, 0, "DOD")
  snl.SNLBusTerm.create(ram32m, snl.SNLTerm.Direction.Input, 4, 0, "ADDRA")
  snl.SNLBusTerm.create(ram32m, snl.SNLTerm.Direction.Input, 4, 0, "ADDRB")
  snl.SNLBusTerm.create(ram32m, snl.SNLTerm.Direction.Input, 4, 0, "ADDRC")
  snl.SNLBusTerm.create(ram32m, snl.SNLTerm.Direction.Input, 4, 0, "ADDRD")
  snl.SNLBusTerm.create(ram32m, snl.SNLTerm.Direction.Input, 1, 0, "DIA")
  snl.SNLBusTerm.create(ram32m, snl.SNLTerm.Direction.Input, 1, 0, "DIB")
  snl.SNLBusTerm.create(ram32m, snl.SNLTerm.Direction.Input, 1, 0, "DIC")
  snl.SNLBusTerm.create(ram32m, snl.SNLTerm.Direction.Input, 1, 0, "DID")
  snl.SNLScalarTerm.create(ram32m, snl.SNLTerm.Direction.Input, "WCLK")
  snl.SNLScalarTerm.create(ram32m, snl.SNLTerm.Direction.Input, "WE")
  snl.SNLParameter.create_binary(ram32m, "INIT_A", 64, 0)
  snl.SNLParameter.create_binary(ram32m, "INIT_B", 64, 0)
  snl.SNLParameter.create_binary(ram32m, "INIT_C", 64, 0)
  snl.SNLParameter.create_binary(ram32m, "INIT_D", 64, 0)

def constructRAM64M(lib):
  ram64m = snl.SNLDesign.createPrimitive(lib, "RAM64M")
  snl.SNLScalarTerm.create(ram64m, snl.SNLTerm.Direction.Output, "DOA")
  snl.SNLScalarTerm.create(ram64m, snl.SNLTerm.Direction.Output, "DOB")
  snl.SNLScalarTerm.create(ram64m, snl.SNLTerm.Direction.Output, "DOC")
  snl.SNLScalarTerm.create(ram64m, snl.SNLTerm.Direction.Output, "DOD")
  snl.SNLBusTerm.create(ram64m, snl.SNLTerm.Direction.Input, 5, 0, "ADDRA")
  snl.SNLBusTerm.create(ram64m, snl.SNLTerm.Direction.Input, 5, 0, "ADDRB")
  snl.SNLBusTerm.create(ram64m, snl.SNLTerm.Direction.Input, 5, 0, "ADDRC")
  snl.SNLBusTerm.create(ram64m, snl.SNLTerm.Direction.Input, 5, 0, "ADDRD")
  snl.SNLScalarTerm.create(ram64m, snl.SNLTerm.Direction.Input, "DIA")
  snl.SNLScalarTerm.create(ram64m, snl.SNLTerm.Direction.Input, "DIB")
  snl.SNLScalarTerm.create(ram64m, snl.SNLTerm.Direction.Input, "DIC")
  snl.SNLScalarTerm.create(ram64m, snl.SNLTerm.Direction.Input, "DID")
  snl.SNLScalarTerm.create(ram64m, snl.SNLTerm.Direction.Input, "WCLK")
  snl.SNLScalarTerm.create(ram64m, snl.SNLTerm.Direction.Input, "WE")
  snl.SNLParameter.create_binary(ram64m, "INIT_A", 64, 0)
  snl.SNLParameter.create_binary(ram64m, "INIT_B", 64, 0)
  snl.SNLParameter.create_binary(ram64m, "INIT_C", 64, 0)
  snl.SNLParameter.create_binary(ram64m, "INIT_D", 64, 0)

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
  snl.SNLParameter.create_string(ramb36e1, "RAM_EXTENSION_A", "NONE")
  snl.SNLParameter.create_string(ramb36e1, "RAM_EXTENSION_B", "NONE")
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
  constructDSP48E1(lib)
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
  constructFDCE(lib)
  constructFDPE(lib)
  constructFDRE(lib)
  constructFDSE(lib)
  constructRAM32M(lib)
  constructRAM64M(lib)
  constructRAMB18E1(lib)
  constructRAMB36E1(lib)
