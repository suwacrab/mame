// license:CC0
// copyright-holders:Ryan Holtz, Ivan Vangelista
//
// Netlist for Atari's Flyball
//
// Derived from the schematics in the manual.
//
// Known problems/issues:
//    * None.
//

#include "netlist/devices/net_lib.h"

static NETLIST_START(NE556_DIP)
	NE555(A)
	NE555(B)

	NET_C(A.GND, B.GND)
	NET_C(A.VCC, B.VCC)

	DIPPINS(      /*        +--------------+        */
		 A.DISCH, /* 1DISCH |1     ++    14| VCC    */ A.VCC,
		A.THRESH, /* 1THRES |2           13| 2DISCH */ B.DISCH,
		  A.CONT, /*  1CONT |3           12| 2THRES */ B.THRESH,
		 A.RESET, /* 1RESET |4   NE556   11| 2CONT  */ B.CONT,
		   A.OUT, /*   1OUT |5           10| 2RESET */ B.RESET,
		  A.TRIG, /*  1TRIG |6            9| 2OUT   */ B.OUT,
		   A.GND, /*    GND |7            8| 2TRIG  */ B.TRIG
				  /*        +--------------+        */
	)
NETLIST_END()

NETLIST_START(flyball)

	SOLVER(Solver, 48000)
	ANALOG_INPUT(V5, 5)
	ANALOG_INPUT(V18, 18)
	ALIAS(VCC, V5)
	CLOCK(H256, 15750.0)
	CLOCK(V128, 61.5234375)
	NET_C(VCC, H256.VCC, V128.VCC)
	NET_C(GND, H256.GND, V128.GND)

	LOCAL_SOURCE(NE556_DIP)

	TTL_INPUT(BAT_SOUND, 1)
	TTL_INPUT(FOOTSTEP, 1)
	TTL_INPUT(CROWD_SL, 1)
	TTL_INPUT(CROWD_ON, 1)
	TTL_INPUT(CROWD_VL, 1)
	NET_C(VCC, BAT_SOUND.VCC, FOOTSTEP.VCC, CROWD_SL.VCC, CROWD_ON.VCC, CROWD_VL.VCC)
	NET_C(GND, BAT_SOUND.GND, FOOTSTEP.GND, CROWD_SL.GND, CROWD_ON.GND, CROWD_VL.GND)

	RES(R43, RES_K(68)) // RES., CARBON, 5%, 1/4W, 68K
	RES(R73, RES_K(1)) // RES., CARBON, 5%, 1/4W, 1K
	RES(R74, RES_K(1)) // RES., CARBON, 5%, 1/4W, 1K
	POT(R75, RES_K(50)) // TRIMPOT, 50K
	RES(R76, RES_K(100)) // RES., CARBON, 5%, 1/4W, 100K
	RES(R77, 820)  // RES., CARBON, 5%, 1/4W, 820
	RES(R78, RES_K(100)) // RES., CARBON, 5%, 1/4W, 100K
	RES(R79, RES_K(1)) // RES., CARBON, 5%, 1/4W, 820K // Verified as 1K on a real board
	RES(R80, RES_K(330))  // RES., CARBON, 5%, 1/4W, 330 // (330 on parts list, but 330K on schematic, 330 does not work in the netlist)
	RES(R87, RES_K(1)) // RES., CARBON, 5%, 1/4W, 1K
	RES(R88, RES_K(3.3)) // RES., CARBON, 5%, 1/4W, 3.3K
	RES(R89, RES_K(10)) // RES., CARBON, 5%, 1/4W, 10K
	RES(R90, RES_K(10)) // RES., CARBON, 5%, 1/4W, 10K
	RES(R91, RES_K(10)) // RES., CARBON, 5%, 1/4W, 10K
	RES(R92, RES_K(10)) // RES., CARBON, 5%, 1/4W, 10K
	POT(R95, RES_K(10)) // TRIMPOT, 10K
	RES(R96, RES_K(47)) // RES., CARBON, 5%, 1/4W, 47K
	RES(R97A, RES_K(10)) // RES., CARBON, 5%, 1/4W, 10K
	RES(R97B, RES_K(24.4)) // RES., CARBON, 5%, 1/4W, 10K // Verified to exist on a real board
	RES(R98, RES_K(10)) // RES., CARBON, 5%, 1/4W, 10K
	RES(R99, RES_K(33)) // RES., CARBON, 5%, 1/4W, 33K

	CAP(C34, CAP_U(0.0047)) // CAP., MYLAR, .0047uf
	CAP(C44, CAP_U(0.0047)) // CAP., MYLAR, .0047uf
	CAP(C45, CAP_U(0.1)) // CAP., CERAMIC DISC., 0.1 uf, 25V
	CAP(C46, CAP_U(0.015)) // CAP., CERAMIC DISC., 0.015 uf, 25V
	CAP(C47, CAP_U(0.015)) // CAP., CERAMIC DISC., 0.015 uf, 25V
	CAP(C48, CAP_U(10)) // CAP., ELECTROLYTIC, 10 uf, 25V
	CAP(C49, CAP_U(100)) // CAP., ELECTROLYTIC, 100 uf, 25V
	CAP(C51, CAP_U(0.1)) // CAP., CERAMIC DISC., 0.1 uf, 25V
	CAP(C52, CAP_U(0.1)) // CAP., CERAMIC DISC., 0.1 uf, 25V
	CAP(C53, CAP_U(0.1)) // CAP., CERAMIC DISC., 0.1 uf, 25V
	CAP(C79, CAP_U(0.1)) // CAP., CERAMIC DISC., 0.1 uf, 25V
	CAP(C80, CAP_U(0.1)) // CAP., CERAMIC DISC., 0.1 uf, 25V

	TTL_7486_DIP(IC_E7)
	TTL_74164_DIP(IC_B7)
	TTL_74164_DIP(IC_C7)
	TTL_7474_DIP(IC_D7)
	NET_C(VCC, IC_E7.14, IC_B7.14, IC_C7.14, IC_D7.14, IC_E7.13, IC_B7.9, IC_B7.2, IC_C7.9, IC_C7.2)
	NET_C(GND, IC_E7.7,  IC_B7.7,  IC_C7.7,  IC_D7.7,  IC_D7.2, IC_E7.4, IC_E7.5)

	SUBMODEL(NE556_DIP, IC_E8)
	NET_C(VCC, IC_E8.14)
	NET_C(GND, IC_E8.7)

	MC3340_DIP(IC_A8)
	MC3340_DIP(IC_C8)
	NET_C(V18, IC_A8.8, IC_C8.8)
	NET_C(GND, IC_A8.3, IC_C8.3)

	UA741_DIP8(IC_D8)
	NET_C(V18, IC_D8.7)
	NET_C(GND, IC_D8.4)

	// Random Noise Generator
	NET_C(H256.Q, IC_B7.8, IC_C7.8, IC_D7.11, IC_D7.4)
	NET_C(VCC, IC_D7.13, IC_D7.1)
	NET_C(IC_B7.13, IC_C7.1)
	NET_C(IC_C7.13, IC_D7.12)
	NET_C(IC_D7.9, IC_E7.9)
	NET_C(IC_B7.5, IC_E7.10)
	NET_C(IC_E7.8, IC_E7.12)
	NET_C(IC_E7.11, IC_B7.1)
	NET_C(IC_D7.5, IC_D7.10)
	NET_C(V128, IC_D7.3)

	// Band Pass Filter
	NET_C(IC_D7.8, R78.1)
	NET_C(R78.2, R77.1, C46.1, C47.1)
	NET_C(GND, R77.2)
	NET_C(C46.2, R80.1, IC_D8.6)
	NET_C(C47.2, R80.2, IC_D8.2)
	NET_C(V5, IC_D8.3)

	// Bat Sound
	NET_C(BAT_SOUND.Q, IC_E8.4, IC_E8.10, IC_E7.1)
	NET_C(V5, IC_E7.2, R73.1, R74.1)
	NET_C(R74.2, R75.3, R75.2, IC_E8.1)
	NET_C(R75.1, R43.1)
	NET_C(R43.2, IC_E8.2, IC_E8.6, C34.1)
	NET_C(R73.2, IC_E8.13, R76.1)
	NET_C(R76.2, IC_E8.12, IC_E8.8, C44.1)
	NET_C(IC_E8.3, IC_E8.11, C45.1)
	NET_C(GND, C34.2, C44.2, C45.2)
	NET_C(IC_E8.5, R91.1)
	NET_C(IC_E8.9, R90.1)
	NET_C(IC_E7.3, R89.1)

	// Footstep Envelope Generator
	NET_C(FOOTSTEP.Q, R88.1)
	NET_C(IC_D7.8, R79.1)
	NET_C(R79.2, C79.1)
	NET_C(C79.2, IC_C8.1)
	NET_C(R88.2, C48.1, IC_C8.2)
	NET_C(GND, C48.2)
	NET_C(IC_C8.7, R92.1)

	// Crowd & Whistle Volume Control
	NET_C(IC_D8.6, R87.1)
	NET_C(R87.2, C80.1)
	NET_C(C80.2, IC_A8.1)
	NET_C(CROWD_VL.Q, R97A.2, R97B.2)
	NET_C(CROWD_ON.Q, R98.2)
	NET_C(CROWD_SL.Q, R99.2)
	NET_C(R97A.1, R97B.1, R98.1, R99.1, C49.1, IC_A8.2)
	NET_C(GND, C49.2)
	NET_C(IC_A8.7, R96.1)

	// Mixer
	NET_C(R89.2, R90.2, R91.2, R92.2, R96.2, C51.1, R95.3)
	NET_C(GND, C51.2, R95.1)
	NET_C(R95.2, C53.1)
	NET_C(C53.2, C52.1)
	NET_C(C52.2, GND)
	ALIAS(OUTPUT, C53.2)

	// Unconnected pins
	HINT(IC_A8.6, NC)
	HINT(IC_C8.6, NC)
	HINT(IC_B7.2, NC)
	HINT(IC_B7.9, NC)
	HINT(IC_B7.3, NC)
	HINT(IC_B7.4, NC)
	HINT(IC_B7.6, NC)
	HINT(IC_B7.10, NC)
	HINT(IC_B7.11, NC)
	HINT(IC_B7.12, NC)
	HINT(IC_C7.3, NC)
	HINT(IC_C7.4, NC)
	HINT(IC_C7.5, NC)
	HINT(IC_C7.6, NC)
	HINT(IC_C7.10, NC)
	HINT(IC_C7.11, NC)
	HINT(IC_C7.12, NC)
	HINT(IC_D7.6, NC)
	HINT(IC_E7.6, NC)
NETLIST_END()
