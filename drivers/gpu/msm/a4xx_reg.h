/* Copyright (c) 2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _A4XX_REG_H
#define _A4XX_REG_H

/* RB registers */
#define A4XX_RB_GMEM_BASE_ADDR		0xcc0

#define A4XX_RB_PERFCTR_RB_SEL_0	0xcc7
#define A4XX_RB_PERFCTR_RB_SEL_1	0xcc8
#define A4XX_RB_PERFCTR_RB_SEL_2	0xcc9
#define A4XX_RB_PERFCTR_RB_SEL_3	0xcca
#define A4XX_RB_PERFCTR_RB_SEL_4	0xccb
#define A4XX_RB_PERFCTR_RB_SEL_5	0xccc
#define A4XX_RB_PERFCTR_RB_SEL_6	0xccd
#define A4XX_RB_PERFCTR_RB_SEL_7	0xcce

enum a4xx_rb_perfctr_rb_sel {
	RB_VALID_SAMPLES = 0x25,
	RB_Z_FAIL = 0x28,
	RB_S_FAIL = 0x29,
};

/* RBBM registers */
#define A4XX_RBBM_AHB_CMD		0x25
#define A4XX_RBBM_SP_HYST_CNT		0x21
#define A4XX_RBBM_SW_RESET_CMD		0x22

#define A4XX_RBBM_AHB_CTL0		0x23
#define A4XX_RBBM_AHB_CTL1		0x24
#define A4XX_RBBM_WAIT_IDLE_CLOCKS_CTL	0x2b
#define A4XX_RBBM_INTERFACE_HANG_INT_CTL	0x2f
#define A4XX_RBBM_RBBM_CTL		0x3e
#define A4XX_RBBM_AHB_ERROR_STATUS	0x18f
#define A4XX_RBBM_STATUS		0x191
#define A4XX_RBBM_INT_CLEAR_CMD		0x36
#define A4XX_RBBM_INT_0_MASK		0x37
#define A4XX_RBBM_INT_0_STATUS		0x17d
#define A4XX_RBBM_PERFCTR_CTL		0x170
#define A4XX_RBBM_PERFCTR_LOAD_CMD0	0x171
#define A4XX_RBBM_PERFCTR_LOAD_CMD1	0x172
#define A4XX_RBBM_PERFCTR_LOAD_CMD2	0x173
#define A4XX_RBBM_GPU_BUSY_MASKED	0x17a
#define A4XX_RBBM_PERFCTR_PWR_1_LO	0x168
#define A4XX_RBBM_PERFCTR_CP_0_LO	0x9c
#define A4XX_RBBM_PERFCTR_CP_1_LO	0x9e
#define A4XX_RBBM_PERFCTR_RBBM_0_LO	0xac
#define A4XX_RBBM_PERFCTR_RBBM_1_LO	0xae
#define A4XX_RBBM_PERFCTR_RBBM_2_LO	0xb0
#define A4XX_RBBM_PERFCTR_RBBM_3_LO	0xb2
#define A4XX_RBBM_PERFCTR_RBBM_SEL_0	0x176
#define A4XX_RBBM_PERFCTR_RBBM_SEL_1	0x177
#define A4XX_RBBM_PERFCTR_RBBM_SEL_2	0x178
#define A4XX_RBBM_PERFCTR_RBBM_SEL_3	0x179

#define A4XX_RBBM_PERFCTR_PC_0_LO	0xb4
#define A4XX_RBBM_PERFCTR_PC_0_HI	0xb5
#define A4XX_RBBM_PERFCTR_PC_1_LO	0xb6
#define A4XX_RBBM_PERFCTR_PC_1_HI	0xb7
#define A4XX_RBBM_PERFCTR_PC_2_LO	0xb8
#define A4XX_RBBM_PERFCTR_PC_2_HI	0xb9
#define A4XX_RBBM_PERFCTR_PC_3_LO	0xba
#define A4XX_RBBM_PERFCTR_PC_3_HI	0xbb
#define A4XX_RBBM_PERFCTR_PC_4_LO	0xbc
#define A4XX_RBBM_PERFCTR_PC_4_HI	0xbd
#define A4XX_RBBM_PERFCTR_PC_5_LO	0xbe
#define A4XX_RBBM_PERFCTR_PC_5_HI	0xbf
#define A4XX_RBBM_PERFCTR_PC_6_LO	0xc0
#define A4XX_RBBM_PERFCTR_PC_6_HI	0xc1
#define A4XX_RBBM_PERFCTR_PC_7_LO	0xc2
#define A4XX_RBBM_PERFCTR_PC_7_HI	0xc3
#define A4XX_RBBM_PERFCTR_VFD_0_LO	0xc4
#define A4XX_RBBM_PERFCTR_VFD_0_HI	0xc5
#define A4XX_RBBM_PERFCTR_VFD_1_LO	0xc6
#define A4XX_RBBM_PERFCTR_VFD_1_HI	0xc7
#define A4XX_RBBM_PERFCTR_VFD_2_LO	0xc8
#define A4XX_RBBM_PERFCTR_VFD_2_HI	0xc9
#define A4XX_RBBM_PERFCTR_VFD_3_LO	0xca
#define A4XX_RBBM_PERFCTR_VFD_3_HI	0xcb
#define A4XX_RBBM_PERFCTR_VFD_4_LO	0xcc
#define A4XX_RBBM_PERFCTR_VFD_4_HI	0xcd
#define A4XX_RBBM_PERFCTR_VFD_5_LO	0xce
#define A4XX_RBBM_PERFCTR_VFD_5_HI	0xcf
#define A4XX_RBBM_PERFCTR_VFD_6_LO	0xd0
#define A4XX_RBBM_PERFCTR_VFD_6_HI	0xd1
#define A4XX_RBBM_PERFCTR_VFD_7_LO	0xd2
#define A4XX_RBBM_PERFCTR_VFD_7_HI	0xd3
#define A4XX_RBBM_PERFCTR_HLSQ_0_LO	0xd4
#define A4XX_RBBM_PERFCTR_HLSQ_0_HI	0xd5
#define A4XX_RBBM_PERFCTR_HLSQ_1_LO	0xd6
#define A4XX_RBBM_PERFCTR_HLSQ_1_HI	0xd7
#define A4XX_RBBM_PERFCTR_HLSQ_2_LO	0xd8
#define A4XX_RBBM_PERFCTR_HLSQ_2_HI	0xd9
#define A4XX_RBBM_PERFCTR_HLSQ_3_LO	0xda
#define A4XX_RBBM_PERFCTR_HLSQ_3_HI	0xdb
#define A4XX_RBBM_PERFCTR_HLSQ_4_LO	0xdc
#define A4XX_RBBM_PERFCTR_HLSQ_4_HI	0xdd
#define A4XX_RBBM_PERFCTR_HLSQ_5_LO	0xde
#define A4XX_RBBM_PERFCTR_HLSQ_5_HI	0xdf
#define A4XX_RBBM_PERFCTR_HLSQ_6_LO	0xe0
#define A4XX_RBBM_PERFCTR_HLSQ_6_HI	0xe1
#define A4XX_RBBM_PERFCTR_HLSQ_7_LO	0xe2
#define A4XX_RBBM_PERFCTR_HLSQ_7_HI	0xe3
#define A4XX_RBBM_PERFCTR_VPC_0_LO	0xe4
#define A4XX_RBBM_PERFCTR_VPC_0_HI	0xe5
#define A4XX_RBBM_PERFCTR_VPC_1_LO	0xe6
#define A4XX_RBBM_PERFCTR_VPC_1_HI	0xe7
#define A4XX_RBBM_PERFCTR_VPC_2_LO	0xe8
#define A4XX_RBBM_PERFCTR_VPC_2_HI	0xe9
#define A4XX_RBBM_PERFCTR_VPC_3_LO	0xea
#define A4XX_RBBM_PERFCTR_VPC_3_HI	0xeb
#define A4XX_RBBM_PERFCTR_CCU_0_LO	0xec
#define A4XX_RBBM_PERFCTR_CCU_0_HI	0xed
#define A4XX_RBBM_PERFCTR_CCU_1_LO	0xee
#define A4XX_RBBM_PERFCTR_CCU_1_HI	0xef
#define A4XX_RBBM_PERFCTR_CCU_2_LO	0xf0
#define A4XX_RBBM_PERFCTR_CCU_2_HI	0xf1
#define A4XX_RBBM_PERFCTR_CCU_3_LO	0xf2
#define A4XX_RBBM_PERFCTR_CCU_3_HI	0xf3
#define A4XX_RBBM_PERFCTR_TSE_0_LO	0xf4
#define A4XX_RBBM_PERFCTR_TSE_0_HI	0xf5
#define A4XX_RBBM_PERFCTR_TSE_1_LO	0xf6
#define A4XX_RBBM_PERFCTR_TSE_1_HI	0xf7
#define A4XX_RBBM_PERFCTR_TSE_2_LO	0xf8
#define A4XX_RBBM_PERFCTR_TSE_2_HI	0xf9
#define A4XX_RBBM_PERFCTR_TSE_3_LO	0xfa
#define A4XX_RBBM_PERFCTR_TSE_3_HI	0xfb
#define A4XX_RBBM_PERFCTR_RAS_0_LO	0xfc
#define A4XX_RBBM_PERFCTR_RAS_0_HI	0xfd
#define A4XX_RBBM_PERFCTR_RAS_1_LO	0xfe
#define A4XX_RBBM_PERFCTR_RAS_1_HI	0xff
#define A4XX_RBBM_PERFCTR_RAS_2_LO	0x100
#define A4XX_RBBM_PERFCTR_RAS_2_HI	0x101
#define A4XX_RBBM_PERFCTR_RAS_3_LO	0x102
#define A4XX_RBBM_PERFCTR_RAS_3_HI	0x103
#define A4XX_RBBM_PERFCTR_UCHE_0_LO	0x104
#define A4XX_RBBM_PERFCTR_UCHE_0_HI	0x105
#define A4XX_RBBM_PERFCTR_UCHE_1_LO	0x106
#define A4XX_RBBM_PERFCTR_UCHE_1_HI	0x107
#define A4XX_RBBM_PERFCTR_UCHE_2_LO	0x108
#define A4XX_RBBM_PERFCTR_UCHE_2_HI	0x109
#define A4XX_RBBM_PERFCTR_UCHE_3_LO	0x10a
#define A4XX_RBBM_PERFCTR_UCHE_3_HI	0x10b
#define A4XX_RBBM_PERFCTR_UCHE_4_LO	0x10c
#define A4XX_RBBM_PERFCTR_UCHE_4_HI	0x10d
#define A4XX_RBBM_PERFCTR_UCHE_5_LO	0x10e
#define A4XX_RBBM_PERFCTR_UCHE_5_HI	0x10f
#define A4XX_RBBM_PERFCTR_UCHE_6_LO	0x110
#define A4XX_RBBM_PERFCTR_UCHE_6_HI	0x111
#define A4XX_RBBM_PERFCTR_UCHE_7_LO	0x112
#define A4XX_RBBM_PERFCTR_UCHE_7_HI	0x113
#define A4XX_RBBM_PERFCTR_TP_0_LO	0x114
#define A4XX_RBBM_PERFCTR_TP_0_HI	0x115
#define A4XX_RBBM_PERFCTR_TP_1_LO	0x116
#define A4XX_RBBM_PERFCTR_TP_1_HI	0x117
#define A4XX_RBBM_PERFCTR_TP_2_LO	0x118
#define A4XX_RBBM_PERFCTR_TP_2_HI	0x119
#define A4XX_RBBM_PERFCTR_TP_3_LO	0x11a
#define A4XX_RBBM_PERFCTR_TP_3_HI	0x11b
#define A4XX_RBBM_PERFCTR_TP_4_LO	0x11c
#define A4XX_RBBM_PERFCTR_TP_4_HI	0x11d
#define A4XX_RBBM_PERFCTR_TP_5_LO	0x11e
#define A4XX_RBBM_PERFCTR_TP_5_HI	0x11f
#define A4XX_RBBM_PERFCTR_TP_6_LO	0x120
#define A4XX_RBBM_PERFCTR_TP_6_HI	0x121
#define A4XX_RBBM_PERFCTR_TP_7_LO	0x122
#define A4XX_RBBM_PERFCTR_TP_7_HI	0x123
#define A4XX_RBBM_PERFCTR_SP_0_LO	0x124
#define A4XX_RBBM_PERFCTR_SP_0_HI	0x125
#define A4XX_RBBM_PERFCTR_SP_1_LO	0x126
#define A4XX_RBBM_PERFCTR_SP_1_HI	0x127
#define A4XX_RBBM_PERFCTR_SP_2_LO	0x128
#define A4XX_RBBM_PERFCTR_SP_2_HI	0x129
#define A4XX_RBBM_PERFCTR_SP_3_LO	0x12a
#define A4XX_RBBM_PERFCTR_SP_3_HI	0x12b
#define A4XX_RBBM_PERFCTR_SP_4_LO	0x12c
#define A4XX_RBBM_PERFCTR_SP_4_HI	0x12d
#define A4XX_RBBM_PERFCTR_SP_5_LO	0x12e
#define A4XX_RBBM_PERFCTR_SP_5_HI	0x12f
#define A4XX_RBBM_PERFCTR_SP_6_LO	0x130
#define A4XX_RBBM_PERFCTR_SP_6_HI	0x131
#define A4XX_RBBM_PERFCTR_SP_7_LO	0x132
#define A4XX_RBBM_PERFCTR_SP_7_HI	0x133
#define A4XX_RBBM_PERFCTR_SP_8_LO	0x134
#define A4XX_RBBM_PERFCTR_SP_8_HI	0x135
#define A4XX_RBBM_PERFCTR_SP_9_LO	0x136
#define A4XX_RBBM_PERFCTR_SP_9_HI	0x137
#define A4XX_RBBM_PERFCTR_SP_10_LO	0x138
#define A4XX_RBBM_PERFCTR_SP_10_HI	0x139
#define A4XX_RBBM_PERFCTR_SP_11_LO	0x13a
#define A4XX_RBBM_PERFCTR_SP_11_HI	0x13b
#define A4XX_RBBM_PERFCTR_RB_0_LO	0x13c
#define A4XX_RBBM_PERFCTR_RB_0_HI	0x13d
#define A4XX_RBBM_PERFCTR_RB_1_LO	0x13e
#define A4XX_RBBM_PERFCTR_RB_1_HI	0x13f
#define A4XX_RBBM_PERFCTR_RB_2_LO	0x140
#define A4XX_RBBM_PERFCTR_RB_2_HI	0x141
#define A4XX_RBBM_PERFCTR_RB_3_LO	0x142
#define A4XX_RBBM_PERFCTR_RB_3_HI	0x143
#define A4XX_RBBM_PERFCTR_RB_4_LO	0x144
#define A4XX_RBBM_PERFCTR_RB_4_HI	0x145
#define A4XX_RBBM_PERFCTR_RB_5_LO	0x146
#define A4XX_RBBM_PERFCTR_RB_5_HI	0x147
#define A4XX_RBBM_PERFCTR_RB_6_LO	0x148
#define A4XX_RBBM_PERFCTR_RB_6_HI	0x149
#define A4XX_RBBM_PERFCTR_RB_7_LO	0x14a
#define A4XX_RBBM_PERFCTR_RB_7_HI	0x14b
#define A4XX_RBBM_PERFCTR_VSC_0_LO	0x14c
#define A4XX_RBBM_PERFCTR_VSC_0_HI	0x14d
#define A4XX_RBBM_PERFCTR_VSC_1_LO	0x14e
#define A4XX_RBBM_PERFCTR_VSC_1_HI	0x14f
#define A4XX_RBBM_PERFCTR_PWR_0_LO	0x166
#define A4XX_RBBM_PERFCTR_PWR_0_HI	0x167
#define A4XX_RBBM_PERFCTR_PWR_1_LO	0x168
#define A4XX_RBBM_PERFCTR_PWR_1_HI	0x169

/* CP registers */
#define A4XX_CP_SCRATCH_REG0		0x578
#define A4XX_CP_SCRATCH_UMASK		0x228
#define A4XX_CP_SCRATCH_ADDR		0x229
#define A4XX_CP_RB_BASE			0x200
#define A4XX_CP_RB_CNTL			0x201
#define A4XX_CP_RB_WPTR			0x205
#define A4XX_CP_RB_RPTR_ADDR		0x203
#define A4XX_CP_RB_RPTR			0x204
#define A4XX_CP_IB1_BASE		0x206
#define A4XX_CP_IB1_BUFSZ		0x207
#define A4XX_CP_IB2_BASE		0x208
#define A4XX_CP_IB2_BUFSZ		0x209
#define A4XX_CP_WFI_PEND_CTR		0x4d2
#define A4XX_CP_ME_CNTL			0x22d
#define A4XX_CP_ME_RAM_WADDR		0x225
#define A4XX_CP_ME_RAM_RADDR		0x226
#define A4XX_CP_ME_RAM_DATA		0x227
#define A4XX_CP_PFP_UCODE_ADDR		0x223
#define A4XX_CP_PFP_UCODE_DATA		0x224
#define A4XX_CP_PROTECT_CTRL		0x250
#define A4XX_CP_DEBUG			0x22e
#define A4XX_CP_PERFCTR_CP_SEL_0	0x500
#define A4XX_CP_PERFCTR_CP_SEL_1	0x501

/* SP registers */
#define A4XX_SP_VS_OBJ_START		0x22e1
#define A4XX_SP_VS_PVT_MEM_ADDR		0x22e3
#define A4XX_SP_FS_OBJ_START		0x22eb
#define A4XX_SP_FS_PVT_MEM_ADDR		0x22ed
#define A4XX_SP_PERFCTR_SP_SEL_0	0xec4
#define A4XX_SP_PERFCTR_SP_SEL_1	0xec5
#define A4XX_SP_PERFCTR_SP_SEL_2	0xec6
#define A4XX_SP_PERFCTR_SP_SEL_3	0xec7
#define A4XX_SP_PERFCTR_SP_SEL_4	0xec8
#define A4XX_SP_PERFCTR_SP_SEL_5	0xec9
#define A4XX_SP_PERFCTR_SP_SEL_6	0xeca
#define A4XX_SP_PERFCTR_SP_SEL_7	0xecb
#define A4XX_SP_PERFCTR_SP_SEL_8	0xecc
#define A4XX_SP_PERFCTR_SP_SEL_9	0xecd
#define A4XX_SP_PERFCTR_SP_SEL_10	0xece
#define A4XX_SP_PERFCTR_SP_SEL_11	0xecf
#define A4XX_SP_VS_PVT_MEM_ADDR		0x22e3
#define A4XX_SP_FS_PVT_MEM_ADDR		0x22ed
#define A4XX_SP_VS_OBJ_START		0x22e1
#define A4XX_SP_FS_OBJ_START		0x22eb

enum a4xx_sp_perfctr_sp_sel {
	SP_FS_STAGE_BARY_INSTRUCTIONS = 0x10,
};

/* VPC registers */
#define A4XX_VPC_DEBUG_RAM_SEL		0xe60
#define A4XX_VPC_DEBUG_RAM_READ		0xe61
#define A4XX_VPC_PERFCTR_VPC_SEL_0	0xe65
#define A4XX_VPC_PERFCTR_VPC_SEL_1	0xe66
#define A4XX_VPC_PERFCTR_VPC_SEL_2	0xe67
#define A4XX_VPC_PERFCTR_VPC_SEL_3	0xe68

/* UCHE register */
#define UCHE_TRAP_BASE_LO               0xe83
#define UCHE_TRAP_BASE_HI               0xe84

/* VSC registers */
#define A4XX_VSC_SIZE_ADDRESS		0xc01
#define A4XX_VSC_PIPE_DATA_ADDRESS_0	0xc10
#define A4XX_VSC_PIPE_DATA_ADDRESS_1	0xc11
#define A4XX_VSC_PIPE_DATA_ADDRESS_2	0xc12
#define A4XX_VSC_PIPE_DATA_ADDRESS_3	0xc13
#define A4XX_VSC_PIPE_DATA_ADDRESS_4	0xc14
#define A4XX_VSC_PIPE_DATA_ADDRESS_5	0xc15
#define A4XX_VSC_PIPE_DATA_ADDRESS_6	0xc16
#define A4XX_VSC_PIPE_DATA_ADDRESS_7	0xc17
#define A4XX_VSC_PIPE_DATA_LENGTH_0	0xc18
#define A4XX_VSC_PIPE_DATA_LENGTH_1	0xc19
#define A4XX_VSC_PIPE_DATA_LENGTH_2	0xc1a
#define A4XX_VSC_PIPE_DATA_LENGTH_3	0xc1b
#define A4XX_VSC_PIPE_DATA_LENGTH_4	0xc1c
#define A4XX_VSC_PIPE_DATA_LENGTH_5	0xc1d
#define A4XX_VSC_PIPE_DATA_LENGTH_6	0xc1e
#define A4XX_VSC_PIPE_DATA_LENGTH_7	0xc1f
#define A4XX_VSC_PERFCTR_VSC_SEL_0	0xc50
#define A4XX_VSC_PERFCTR_VSC_SEL_1	0xc51

/* VFD registers */
#define A4XX_VFD_CONTROL_0		0x2200
#define A4XX_VFD_FETCH_INSTR_0_0	0x220a
#define A4XX_VFD_FETCH_INSTR_1_31	0x2287
#define A4XX_VFD_PERFCTR_VFD_SEL_0	0xe43
#define A4XX_VFD_PERFCTR_VFD_SEL_1	0xe44
#define A4XX_VFD_PERFCTR_VFD_SEL_2	0xe45
#define A4XX_VFD_PERFCTR_VFD_SEL_3	0xe46
#define A4XX_VFD_PERFCTR_VFD_SEL_4	0xe47
#define A4XX_VFD_PERFCTR_VFD_SEL_5	0xe48
#define A4XX_VFD_PERFCTR_VFD_SEL_6	0xe49
#define A4XX_VFD_PERFCTR_VFD_SEL_7	0xe4a
#define A4XX_VFD_FETCH_INSTR_1_0	0x220b
#define A4XX_VFD_FETCH_INSTR_1_1	0x220f
#define A4XX_VFD_FETCH_INSTR_1_2	0x2213
#define A4XX_VFD_FETCH_INSTR_1_3	0x2217
#define A4XX_VFD_FETCH_INSTR_1_4	0x221b
#define A4XX_VFD_FETCH_INSTR_1_5	0x221f
#define A4XX_VFD_FETCH_INSTR_1_6	0x2223
#define A4XX_VFD_FETCH_INSTR_1_7	0x2227
#define A4XX_VFD_FETCH_INSTR_1_8	0x222b
#define A4XX_VFD_FETCH_INSTR_1_9	0x222f
#define A4XX_VFD_FETCH_INSTR_1_10	0x2233
#define A4XX_VFD_FETCH_INSTR_1_11	0x2237
#define A4XX_VFD_FETCH_INSTR_1_12	0x223b
#define A4XX_VFD_FETCH_INSTR_1_13	0x223f
#define A4XX_VFD_FETCH_INSTR_1_14	0x2243
#define A4XX_VFD_FETCH_INSTR_1_15	0x2247
#define A4XX_VFD_FETCH_INSTR_1_16	0x224b
#define A4XX_VFD_FETCH_INSTR_1_17	0x224f
#define A4XX_VFD_FETCH_INSTR_1_18	0x2253
#define A4XX_VFD_FETCH_INSTR_1_19	0x2257
#define A4XX_VFD_FETCH_INSTR_1_20	0x225b
#define A4XX_VFD_FETCH_INSTR_1_21	0x225f
#define A4XX_VFD_FETCH_INSTR_1_22	0x2263
#define A4XX_VFD_FETCH_INSTR_1_23	0x2267
#define A4XX_VFD_FETCH_INSTR_1_24	0x226b
#define A4XX_VFD_FETCH_INSTR_1_25	0x226f
#define A4XX_VFD_FETCH_INSTR_1_26	0x2273
#define A4XX_VFD_FETCH_INSTR_1_27	0x2277
#define A4XX_VFD_FETCH_INSTR_1_28	0x227b
#define A4XX_VFD_FETCH_INSTR_1_29	0x227f
#define A4XX_VFD_FETCH_INSTR_1_30	0x2283
#define A4XX_VFD_FETCH_INSTR_1_31	0x2287


enum a4xx_vfd_perfctr_vfd_sel {
	VFD_VPC_BYPASS_TRANS = 0x2,
	VFD_UPPER_SHADER_FIBERS = 0xb,
	VFD_LOWER_SHADER_FIBERS = 0xc,
};

/* VBIF registers */
#define A4XX_VBIF_ABIT_SORT		0x301c
#define A4XX_VBIF_ABIT_SORT_CONF	0x301d
#define A4XX_VBIF_GATE_OFF_WRREQ_EN	0x302a
#define A4XX_VBIF_IN_RD_LIM_CONF0	0x302c
#define A4XX_VBIF_IN_RD_LIM_CONF1	0x302d
#define A4XX_VBIF_IN_WR_LIM_CONF0	0x3030
#define A4XX_VBIF_IN_WR_LIM_CONF1	0x3031
#define A4XX_VBIF_ROUND_ROBIN_QOS_ARB	0x3049

#define A4XX_VBIF_PERF_CNT_EN0		0x30c0
#define A4XX_VBIF_PERF_CNT_EN1		0x30c1
#define A4XX_VBIF_PERF_CNT_EN2		0x30c2
#define A4XX_VBIF_PERF_CNT_EN3		0x30c3
#define A4XX_VBIF_PERF_CNT_CLR0		0x30c8
#define A4XX_VBIF_PERF_CNT_CLR1		0x30c9
#define A4XX_VBIF_PERF_CNT_CLR2		0x30ca
#define A4XX_VBIF_PERF_CNT_CLR3		0x30cb
#define A4XX_VBIF_PERF_CNT_SEL0		0x30d0
#define A4XX_VBIF_PERF_CNT_SEL1		0x30d1
#define A4XX_VBIF_PERF_CNT_SEL2		0x30d2
#define A4XX_VBIF_PERF_CNT_SEL3		0x30d3
#define A4XX_VBIF_PERF_CNT_LOW0		0x30d8
#define A4XX_VBIF_PERF_CNT_LOW1		0x30d9
#define A4XX_VBIF_PERF_CNT_LOW2		0x30da
#define A4XX_VBIF_PERF_CNT_LOW3		0x30db
#define A4XX_VBIF_PERF_CNT_HIGH0	0x30e0
#define A4XX_VBIF_PERF_CNT_HIGH1	0x30e1
#define A4XX_VBIF_PERF_CNT_HIGH2	0x30e2
#define A4XX_VBIF_PERF_CNT_HIGH3	0x30e3

#define A4XX_VBIF_PERF_CNT_SEL_MASK	0x7F

/* offset of clear register from select register */
#define A4XX_VBIF_PERF_CLR_REG_SEL_OFF	8
/* offset of enable register from select register */
#define A4XX_VBIF_PERF_EN_REG_SEL_OFF	16
/* offset of high counter from low counter value */
#define A4XX_VBIF_PERF_HIGH_REG_LOW_OFF	8

#define A4XX_VBIF_PERF_PWR_CNT_EN0	0x3100
#define A4XX_VBIF_PERF_PWR_CNT_EN1	0x3101
#define A4XX_VBIF_PERF_PWR_CNT_EN2	0x3102
#define A4XX_VBIF_PERF_PWR_CNT_EN3	0x3103
#define A4XX_VBIF_PERF_PWR_CNT_CLR0	0x3108
#define A4XX_VBIF_PERF_PWR_CNT_CLR1	0x3109
#define A4XX_VBIF_PERF_PWR_CNT_CLR2	0x310A
#define A4XX_VBIF_PERF_PWR_CNT_CLR3	0x310B
#define A4XX_VBIF_PERF_PWR_CNT_LOW0	0x3110
#define A4XX_VBIF_PERF_PWR_CNT_LOW1	0x3111
#define A4XX_VBIF_PERF_PWR_CNT_LOW2	0x3112
#define A4XX_VBIF_PERF_PWR_CNT_LOW3	0x3113
#define A4XX_VBIF_PERF_PWR_CNT_HIGH0	0x3118
#define A4XX_VBIF_PERF_PWR_CNT_HIGH1	0x3119
#define A4XX_VBIF_PERF_PWR_CNT_HIGH2	0x311a
#define A4XX_VBIF_PERF_PWR_CNT_HIGH3	0x311b

/* offset of clear register from the enable register */
#define A4XX_VBIF_PERF_PWR_CLR_REG_EN_OFF	8
/* offset of high counter from low counter value */
#define A4XX_VBIF_PERF_PWR_HIGH_REG_LOW_OFF	8

/* Bit flags for RBBM_CTL */
#define A4XX_RBBM_RBBM_CTL_RESET_PWR_CTR0  BIT(0)
#define A4XX_RBBM_RBBM_CTL_RESET_PWR_CTR1  BIT(1)
#define A4XX_RBBM_RBBM_CTL_ENABLE_PWR_CTR0  BIT(4)
#define A4XX_RBBM_RBBM_CTL_ENABLE_PWR_CTR1  BIT(5)

/* GRAS registers */
#define A4XX_GRAS_PERFCTR_TSE_SEL_0	0xc88
#define A4XX_GRAS_PERFCTR_TSE_SEL_1	0xc89
#define A4XX_GRAS_PERFCTR_TSE_SEL_2	0xc8a
#define A4XX_GRAS_PERFCTR_TSE_SEL_3	0xc8b
#define A4XX_GRAS_PERFCTR_RAS_SEL_0	0xc8c
#define A4XX_GRAS_PERFCTR_RAS_SEL_1	0xc8d
#define A4XX_GRAS_PERFCTR_RAS_SEL_2	0xc8e
#define A4XX_GRAS_PERFCTR_RAS_SEL_3	0xc8f

/* PC registers */
#define A4XX_PC_PERFCTR_PC_SEL_0	0xd10
#define A4XX_PC_PERFCTR_PC_SEL_1	0xd11
#define A4XX_PC_PERFCTR_PC_SEL_2	0xd12
#define A4XX_PC_PERFCTR_PC_SEL_3	0xd13
#define A4XX_PC_PERFCTR_PC_SEL_4	0xd14
#define A4XX_PC_PERFCTR_PC_SEL_5	0xd15
#define A4XX_PC_PERFCTR_PC_SEL_6	0xd16
#define A4XX_PC_PERFCTR_PC_SEL_7	0xd17

enum a4xx_pc_perfctr_pc_sel {
	PC_INSTANCES = 0x1,
	PC_VERTEX_HITS = 0x8,
	PC_GENERATED_FIBERS = 0x12,
	PC_GENERATED_WAVES = 0x13,
};

/* HLSQ registers */
#define A4XX_HLSQ_PERFCTR_HLSQ_SEL_0	0xe06
#define A4XX_HLSQ_PERFCTR_HLSQ_SEL_1	0xe07
#define A4XX_HLSQ_PERFCTR_HLSQ_SEL_2	0xe08
#define A4XX_HLSQ_PERFCTR_HLSQ_SEL_3	0xe09
#define A4XX_HLSQ_PERFCTR_HLSQ_SEL_4	0xe0a
#define A4XX_HLSQ_PERFCTR_HLSQ_SEL_5	0xe0b
#define A4XX_HLSQ_PERFCTR_HLSQ_SEL_6	0xe0c
#define A4XX_HLSQ_PERFCTR_HLSQ_SEL_7	0xe0d

enum a4xx_hlsq_perfctr_hlsq_sel {
	HLSQ_SP_VS_STAGE_CONSTANT = 0x0,
	HLSQ_SP_VS_STAGE_INSTRUCTIONS = 0x1,
	HLSQ_SP_FS_STAGE_CONSTANT = 0x2,
	HLSQ_SP_FS_STAGE_INSTRUCTIONS = 0x3,
	HLSQ_FS_STAGE_16_WAVES = 0x8,
	HLSQ_FS_STAGE_32_WAVES = 0x9,
	HLSQ_FS_STAGE_64_WAVES = 0xa,
	HLSQ_VS_STAGE_16_WAVES = 0xb,
	HLSQ_VS_STAGE_32_WAVES = 0xc,
};

/* CCU registers */
#define A4XX_RB_PERFCTR_CCU_SEL_0	0xccf
#define A4XX_RB_PERFCTR_CCU_SEL_1	0xcd0
#define A4XX_RB_PERFCTR_CCU_SEL_2	0xcd1
#define A4XX_RB_PERFCTR_CCU_SEL_3	0xcd2

enum a4xx_cu_perfctr_ccu_sel {
	CCU_VBIF_STALL = 0x1,
	CCU_VBIF_LATENCY_CYCLES = 0x4,
	CCU_VBIF_LATENCY_SAMPLES = 0x5,
	CCU_Z_READ = 0x13,
	CCU_Z_WRITE = 0x14,
	CCU_C_READ = 0x15,
	CCU_C_WRITE = 0x16,
};

/* UCHE registers */
#define A4XX_UCHE_PERFCTR_UCHE_SEL_0	0xe8e
#define A4XX_UCHE_PERFCTR_UCHE_SEL_1	0xe8f
#define A4XX_UCHE_PERFCTR_UCHE_SEL_2	0xe90
#define A4XX_UCHE_PERFCTR_UCHE_SEL_3	0xe91
#define A4XX_UCHE_PERFCTR_UCHE_SEL_4	0xe92
#define A4XX_UCHE_PERFCTR_UCHE_SEL_5	0xe93
#define A4XX_UCHE_PERFCTR_UCHE_SEL_6	0xe94
#define A4XX_UCHE_PERFCTR_UCHE_SEL_7	0xe95

/* TPL1 registers */
enum a4xx_uche_perfctr_uche_sel {
	UCHE_READ_REQUESTS_MARB = 0x8,
	UCHE_READ_REQUESTS_SP = 0x9,
	UCHE_WRITE_REQUESTS_MARB = 0xa,
	UCHE_WRITE_REQUESTS_SP = 0xb,
	UCHE_WRITE_REQUESTS_VPC = 0x14,
};

/* TPL1 registers */
#define A4XX_TPL1_PERFCTR_TP_SEL_0	0xf04
#define A4XX_TPL1_PERFCTR_TP_SEL_1	0xf05
#define A4XX_TPL1_PERFCTR_TP_SEL_2	0xf06
#define A4XX_TPL1_PERFCTR_TP_SEL_3	0xf07
#define A4XX_TPL1_PERFCTR_TP_SEL_4	0xf08
#define A4XX_TPL1_PERFCTR_TP_SEL_5	0xf09
#define A4XX_TPL1_PERFCTR_TP_SEL_6	0xf0a
#define A4XX_TPL1_PERFCTR_TP_SEL_7	0xf0b

enum a4xx_tpl1_perfctr_tp_sel {
	TP_OUTPUT_TEXELS_POINT = 0x2,
	TP_OUTPUT_TEXELS_BILINEAR = 0x3,
	TP_OUTPUT_TEXELS_MIP = 0x4,
	TP_OUTPUT_TEXELS_ANISO = 0x5,
	TP_OUTPUT_TEXELS_OPS16 = 0x6,
	TP_OUTPUT_TEXELS_OPS32 = 0x7,
	TP_ZERO_LOD = 0xe,
	TP_LATENCY = 0x12,
	TP_LATENCY_TRANS = 0x13,
};

#endif /* _A4XX_REG_H */
