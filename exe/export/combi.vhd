library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity f is
	Port (
		qq: in std_logic;
		B: in std_logic;
		sss: out std_logic;
		SSS: out std_logic
		);
end f;

architecture behavioral of f is
begin
	sss<=((qq))
	SSS<=((not(qq)))
end behavioral;
