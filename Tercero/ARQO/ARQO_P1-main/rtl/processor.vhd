--------------------------------------------------------------------------------
-- Procesador MIPS con pipeline curso Arquitectura 2021-2022
--
-- (INCLUIR AQUI LA INFORMACION SOBRE LOS AUTORES)
--
--------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity processor is
   port(
      Clk         : in  std_logic; -- Reloj activo en flanco subida
      Reset       : in  std_logic; -- Reset asincrono activo nivel alto
      -- Instruction memory
      IAddr      : out std_logic_vector(31 downto 0); -- Direccion Instr
      IDataIn    : in  std_logic_vector(31 downto 0); -- Instruccion leida
      -- Data memory
      DAddr      : out std_logic_vector(31 downto 0); -- Direccion
      DRdEn      : out std_logic;                     -- Habilitacion lectura
      DWrEn      : out std_logic;                     -- Habilitacion escritura
      DDataOut   : out std_logic_vector(31 downto 0); -- Dato escrito
      DDataIn    : in  std_logic_vector(31 downto 0)  -- Dato leido
   );
end processor;

architecture rtl of processor is

  component alu
    port(
      OpA      : in std_logic_vector (31 downto 0);
      OpB      : in std_logic_vector (31 downto 0);
      Control  : in std_logic_vector (3 downto 0);
      Result   : out std_logic_vector (31 downto 0);
      Signflag : out std_logic;
      Zflag    : out std_logic
    );
  end component;


  component reg_bank
     port (
        Clk   : in std_logic; -- Reloj activo en flanco de subida
        Reset : in std_logic; -- Reset as�ncrono a nivel alto
        A1    : in std_logic_vector(4 downto 0);   -- Direcci�n para el puerto Rd1
        Rd1   : out std_logic_vector(31 downto 0); -- Dato del puerto Rd1
        A2    : in std_logic_vector(4 downto 0);   -- Direcci�n para el puerto Rd2
        Rd2   : out std_logic_vector(31 downto 0); -- Dato del puerto Rd2
        A3    : in std_logic_vector(4 downto 0);   -- Direcci�n para el puerto Wd3
        Wd3   : in std_logic_vector(31 downto 0);  -- Dato de entrada Wd3
        We3   : in std_logic -- Habilitaci�n de la escritura de Wd3
     );
  end component reg_bank;

  component control_unit
     port (
        -- Entrada = codigo de operacion en la instruccion:
        OpCode   : in  std_logic_vector (5 downto 0);
        -- Seniales para el PC
        Branch   : out  std_logic; -- 1 = Ejecutandose instruccion branch
        -- Seniales relativas a la memoria
        MemToReg : out  std_logic; -- 1 = Escribir en registro la salida de la mem.
        MemWrite : out  std_logic; -- Escribir la memoria
        MemRead  : out  std_logic; -- Leer la memoria
        -- Seniales para la ALU
        ALUSrc   : out  std_logic;                     -- 0 = oper.B es registro, 1 = es valor inm.
        ALUOp    : out  std_logic_vector (2 downto 0); -- Tipo operacion para control de la ALU
        -- Seniales para el GPR
        RegWrite : out  std_logic; -- 1 = Escribir registro
        RegDst   : out  std_logic  -- 0 = Reg. destino es rt, 1=rd
     );
  end component;

  component alu_control is
   port (
      -- Entradas:
      ALUOp                       : in std_logic_vector (2 downto 0); -- Codigo de control desde la unidad de control
      Funct                       : in std_logic_vector (5 downto 0); -- Campo "funct" de la instruccion
      -- Salida de control para la ALU:
      ALUControl                  : out std_logic_vector (3 downto 0) -- Define operacion a ejecutar por la ALU
   );
 end component alu_control;

 signal Alu_Op2                   : std_logic_vector(31 downto 0);
 signal ALU_Igual                 : std_logic;
 signal AluControl                : std_logic_vector(3 downto 0);  

 signal PC_next                   : std_logic_vector(31 downto 0);
 signal PC_reg                    : std_logic_vector(31 downto 0);


 signal Addr_Jump                 : std_logic_vector(31 downto 0);
 signal Addr_Jump_dest            : std_logic_vector(31 downto 0);
 signal desition_Jump, Regs_eq_branch             : std_logic;
 signal Alu_Res                   : std_logic_vector(31 downto 0);

  -- Enablers --
  signal enable_IF_ID, enable_ID_EX, enable_EX_MEM, enable_MEM_WB : std_logic;
  -- IF --
  signal PCPlus4_IF               : std_logic_vector(31 downto 0);
  signal Instruction_IF           : std_logic_vector(31 downto 0); -- La instrucción desde lamem de instr

  -- ID --
  signal MemToReg_ID, RegWrite_ID, MemRead_ID, MemWrite_ID, Branch_ID, RegDst_ID : std_logic;
  signal PCPlus4_ID               : std_logic_vector(31 downto 0);
  signal Instruction_ID           : std_logic_vector(31 downto 0); -- La instrucción desde lamem de instr
  signal Reg_RS_ID, Reg_RT_ID     : std_logic_vector(31 downto 0);
  signal Inm_ext_ID               : std_logic_vector(31 downto 0); -- La parte baja de la instrucción extendida de signo
  signal ALUSrc_ID                : std_logic;
  signal ALUOp_ID                 : std_logic_vector(2 downto 0);
  signal Jump_ID                  : std_logic;
  

  -- EX --
  signal MemToReg_EX, RegWrite_EX, MemRead_EX, MemWrite_EX, Branch_EX ,RegDst_EX : std_logic;
  signal ALUSrc_EX                : std_logic;
  signal PCPlus4_EX               : std_logic_vector(31 downto 0);
  signal Reg_RS_EX                : std_logic_vector(31 downto 0);
  signal Reg_RT_EX                : std_logic_vector(31 downto 0);
  signal Inm_ext_EX               : std_logic_vector(31 downto 0);
  signal Instruction_EX           : std_logic_vector(31 downto 0);
  signal Jump_EX                  : std_logic;
  signal JumpAddress_EX           : std_logic_vector(31 downto 0);
  signal Zero_EX                  : std_logic;
  signal ALU_Res_EX               : std_logic_vector(31 downto 0);
  signal ALUOp_EX                 : std_logic_vector(2 downto 0);
  signal Reg_RD_EX                : std_logic_vector(4 downto 0);
  signal Addr_Branch_EX           : std_logic_vector(31 downto 0);

  -- MEM --
  signal MemToReg_MEM, RegWrite_MEM, MemRead_MEM, MemWrite_MEM   : std_logic;
  signal Branch_MEM               : std_logic; 
  signal PCSrc_MEM                : std_logic; 
  signal Zero_MEM                 : std_logic; -- 1 = Ejecutandose instruccion branch
  signal JumpAddress_MEM          : std_logic_vector(31 downto 0);
  signal ALU_Res_MEM              : std_logic_vector(31 downto 0);
  signal Reg_RT_MEM               : std_logic_vector(31 downto 0);
  signal Reg_RD_MEM               : std_logic_vector(4 downto 0);
  signal dataIn_MEM               : std_logic_vector(31 downto 0);
  signal Jump_MEM                 : std_logic;
  signal Addr_Branch_MEM          : std_logic_vector(31 downto 0);


  
  -- WB --
  signal RegWrite_WB, MemToReg_WB : std_logic;
  signal dataIn_WB                : std_logic_vector(31 downto 0);
  signal ALU_Res_WB               : std_logic_vector(31 downto 0);
  signal Reg_RD_WB                : std_logic_vector(4 downto 0);
  signal Reg_RD_data_WB           : std_logic_vector(31 downto 0);
  -------------------------
begin

  PC_next <= Addr_Jump_dest when PCSrc_MEM = '1' else PCPlus4_IF;

  PC_reg_proc: process(Clk, Reset)
  begin
    if Reset = '1' then
      PC_reg <= (others => '0');
    elsif rising_edge(Clk) then
      PC_reg <= PC_next;
    end if;
  end process;

  PCPlus4_IF               <= PC_reg + 4;
  IAddr                    <= PC_reg;
  Instruction_IF           <= IDataIn; -- Instruction <= IDataIn;

-- peligro -----------

  IF_ID_Regs: process(clk,reset)
  begin
    if reset = '1' then
      PCPlus4_ID           <= (others=>'0');
      Instruction_ID       <= (others=>'0');
    elsif rising_edge(clk) then
      PCPlus4_ID           <= PCPlus4_IF;
      Instruction_ID       <= Instruction_IF;
    end if;
    end process;

  ID_EX_Regs: process(clk,reset)
  begin
    if reset = '1' then
      MemToReg_EX          <= '0';
      RegWrite_EX          <= '0';
      MemRead_EX           <= '0';
      MemWrite_EX          <= '0';
      Branch_EX            <= '0';
      RegDst_EX            <= '0';
      ALUSrc_EX            <= '0';
      Jump_EX              <= '0';
      PCPlus4_EX           <= (others=>'0');
      ALUOp_EX             <= (others=>'0');
      Reg_RS_EX            <= (others=>'0');
      Reg_RT_EX            <= (others=>'0');
      Inm_ext_EX           <= (others=>'0');
      Instruction_EX       <= (others=>'0');



    elsif rising_edge(clk) then
        MemToReg_EX        <= MemToReg_ID;
        RegWrite_EX        <= RegWrite_ID;
        PCPlus4_EX         <= PCPlus4_ID;
        MemRead_EX         <= MemRead_ID;
        MemWrite_EX        <= MemWrite_ID;
        Branch_EX          <= Branch_ID;
        PCPlus4_EX         <= PCPlus4_ID;
        Reg_RS_EX          <= Reg_RS_ID;
        Reg_RT_EX          <= Reg_RT_ID;
        Inm_ext_EX         <= Inm_ext_ID;
        Instruction_EX     <= Instruction_ID;
        ALUOp_EX           <= ALUOp_ID;
        ALUSrc_EX          <= ALUSrc_ID;
        RegDst_EX          <= RegDst_ID;
        Jump_EX            <= Jump_ID;

    end if;
  end process;
  

  EX_MEM_Regs: process(clk,reset)
  begin
    if reset = '1' then
      RegWrite_MEM         <= '0';
      MemRead_MEM          <= '0';
      MemWrite_MEM         <= '0';
      Branch_MEM           <= '0';
      JumpAddress_MEM      <= (others=>'0');
      Zero_MEM             <= '0';
      ALU_Res_MEM          <= (others=>'0');
      Reg_RT_MEM           <= (others=>'0');
      Reg_RD_MEM           <= (others=>'0');
      MemToReg_MEM         <= '0';
      Jump_MEM             <= '0';
      Addr_Branch_MEM       <= (others=>'0');


    elsif rising_edge(clk) then
      RegWrite_MEM         <= RegWrite_EX;
      MemToReg_MEM         <= MemToReg_EX; 
      MemRead_MEM          <= MemRead_EX;
      MemWrite_MEM         <= MemWrite_EX;
      Branch_MEM           <= Branch_EX;
      JumpAddress_MEM      <= JumpAddress_EX;
      Zero_MEM             <= Zero_EX;
      ALU_Res_MEM          <= ALU_Res_EX;
      Reg_RT_MEM           <= Reg_RT_EX;
      Reg_RD_MEM           <= Reg_RD_EX;
      Jump_MEM             <= Jump_EX;
      Addr_Branch_MEM      <= Addr_Branch_EX;

    end if;
  end process;
  

  MEM_WB_Regs: process(clk,reset)
  begin
    if reset = '1' then
      RegWrite_WB          <= '0';
      MemToReg_WB          <= '0';
      dataIn_WB            <= (others=>'0');
      ALU_Res_WB           <= (others=>'0');
      Reg_RD_WB            <= (others=>'0');



    elsif rising_edge(clk) then
      RegWrite_WB          <= RegWrite_MEM;
      MemToReg_WB          <= MemToReg_MEM; 
      dataIn_WB            <= dataIn_MEM;
      ALU_Res_WB           <= ALU_Res_MEM;
      Reg_RD_WB            <= Reg_RD_MEM;

    end if;
  end process;


------------------------------------------

  RegsMIPS : reg_bank
  port map (
    Clk   => Clk,
    Reset => Reset,
    A1    => Instruction_ID(25 downto 21),
    Rd1   => Reg_RS_ID,
    A2    => Instruction_ID(20 downto 16),
    Rd2   => Reg_RT_ID,
    A3    => Reg_RD_WB,
    Wd3   => Reg_RD_data_WB,
    We3   => RegWrite_WB
  );

  UnidadControl : control_unit
  port map(
    OpCode   => Instruction_ID(31 downto 26),
    -- Señales para el PC
    --Jump   => CONTROL_JUMP,
    Branch   => Branch_ID,
    -- Señales para la memoria
    MemToReg => MemToReg_ID,
    MemWrite => MemWrite_ID,
    MemRead  => MemRead_ID,
    -- Señales para la ALU
    ALUSrc   => ALUSrc_ID,
    ALUOP    => ALUOP_ID,
    -- Señales para el GPR
    RegWrite => RegWrite_ID,
    
    RegDst   => RegDst_ID
  );


  Inm_ext_ID        <= x"FFFF" & Instruction_ID(15 downto 0) when Instruction_ID(15)='1' else
                    x"0000" & Instruction_ID(15 downto 0);

  JumpAddress_EX     <= PCPlus4_EX(31 downto 28) &  Inm_ext_EX(25 downto 0) & "00";

  Addr_Branch_EX    <= PCPlus4_EX + ( Inm_ext_EX(29 downto 0) & "00");

  Jump_ID      <= '1' when Instruction_ID(31 downto 26) = "000010" else
                    '0'; --nunca salto incondicional

  PCSrc_MEM  <= (Branch_MEM and Zero_MEM) or Jump_MEM; -- Comentario

  Regs_eq_branch <= '1' when (Reg_RS_EX = Reg_RT_EX) else '0'; -- creo que no se usa jeje salu3
  
  Addr_Jump_dest <= JumpAddress_MEM   when Jump_MEM='1' else
                    Addr_Branch_MEM when Branch_MEM='1' else
                    (others =>'0');


                    
  

  Alu_control_i: alu_control
  port map(
    -- Entradas:
    ALUOp  => ALUOp_EX, -- Codigo de control desde la unidad de control
    Funct  => Inm_ext_EX(5 downto 0), -- Campo "funct" de la instruccion
    -- Salida de control para la ALU:
    ALUControl => ALUControl -- Define operacion a ejecutar por la ALU
    );

Alu_MIPS : alu
  port map (
    OpA          => Reg_RS_EX,
    OpB          => Alu_Op2,
    Control      => ALUControl, -- Control  => AluControl,
    Result       => ALU_Res_EX,
    Signflag     => open,
    Zflag        => Zero_EX
  );

  Alu_Op2       <= Reg_RT_EX when ALUSrc_EX = '0' else Inm_ext_EX;
  Reg_RD_EX     <= Instruction_EX(20 downto 16) when RegDst_EX = '0' else Instruction_EX(15 downto 11);
  DAddr         <= ALU_Res_MEM;
  DDataOut      <= Reg_RT_MEM;
  DWrEn         <= MemWrite_MEM;
  dRdEn         <= MemRead_MEM;
  dataIn_MEM    <= DDataIn;

 Reg_RD_data_WB <= dataIn_WB when MemToReg_WB = '1' else Alu_Res_WB;
                  

end architecture;
