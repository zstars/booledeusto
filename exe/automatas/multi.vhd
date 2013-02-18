library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Multisalida is
	Port (
		aa: in std_logic;
		bb: in std_logic;
		cc: in std_logic;
		dd: in std_logic;
		s1: out std_logic;
		s2: out std_logic;
		s3: out std_logic
		);
end Multisalida;

architecture behavioral of Multisalida is
begin
	s1<='0'
	s2<='1'
	s3<=((aa and dd) or (aa and bb) or (bb and dd) or (not(aa) and cc and not(dd)) or (not(aa) and not(bb) and not(cc)))
end behavioral;
