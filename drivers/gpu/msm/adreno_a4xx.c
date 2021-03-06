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

#include "adreno.h"
#include "a4xx_reg.h"
#include "adreno_a3xx.h"
#include "adreno_cp_parser.h"

/*
 * Set of registers to dump for A4XX on postmortem and snapshot.
 * Registers in pairs - first value is the start offset, second
 * is the stop offset (inclusive)
 */

const unsigned int a4xx_registers[] = {
	/* RBBM */
	0x0000, 0x0002, 0x0004, 0x0021, 0x0023, 0x0024, 0x0026, 0x0026,
	0x0028, 0x002B, 0x002E, 0x0034, 0x0037, 0x0044, 0x0047, 0x0066,
	0x0068, 0x0095, 0x009C, 0x0170, 0x0174, 0x01AF,
	/* CP */
	0x0200, 0x0233, 0x0240, 0x0250, 0x04C0, 0x04DD, 0x0500, 0x050B,
	0x0578, 0x058F,
	/* VSC */
	0x0C00, 0x0C03, 0x0C08, 0x0C41, 0x0C50, 0x0C51,
	/* GRAS */
	0x0C80, 0x0C81, 0x0C88, 0x0C8F,
	/* RB */
	0x0CC0, 0x0CC0, 0x0CC4, 0x0CD2,
	/* PC */
	0x0D00, 0x0D0C, 0x0D10, 0x0D17, 0x0D20, 0x0D23,
	/* HLSQ */
	0x0E00, 0x0E00, 0x0E04, 0x0E0E, 0x0E30, 0x0E30,
	/* VFD */
	0x0E40, 0x0E4A,
	/* VPC */
	0x0E60, 0x0E61, 0x0E63, 0x0E68,
	/* UCHE */
	0x0E80, 0x0E84, 0x0E88, 0x0E95,
	/* SP */
	0x0EC0, 0x0ECF,
	/* TPL1 */
	0x0F00, 0x0F0B,
	/* VMIDMT */
	0x1000, 0x1000, 0x1002, 0x1002, 0x1004, 0x1004, 0x1008, 0x100A,
	0x100C, 0x100D, 0x100F, 0x1010, 0x1012, 0x1016, 0x1024, 0x1024,
	0x1027, 0x1027, 0x1100, 0x1100, 0x1102, 0x1102, 0x1104, 0x1104,
	0x1110, 0x1110, 0x1112, 0x1116, 0x1124, 0x1124, 0x1300, 0x1300,
	0x1380, 0x1380,
	/* GRAS CTX 0 */
	0x2000, 0x2004, 0x2008, 0x2067, 0x2070, 0x2078, 0x207B, 0x216E,
	/* PC CTX 0 */
	0x21C0, 0x21C6, 0x21D0, 0x21D0, 0x21D9, 0x21D9, 0x21E5, 0x21E7,
	/* VFD CTX 0 */
	0x2200, 0x2204, 0x2208, 0x22A9,
	/* SP CTX 0 */
	0x22C0, 0x22C1, 0x22C4, 0x22E5, 0x22E8, 0x22F8, 0x2300, 0x2306,
	0x230C, 0x2312, 0x2318, 0x2339, 0x2340, 0x2360,
	/* TPL1 CTX 0 */
	0x2380, 0x2382, 0x2384, 0x238F, 0x23A0, 0x23A6,
	/* HLSQ CTX 0 */
	0x23C0, 0x23DB,
	/* GRAS CTX 1 */
	0x2400, 0x2404, 0x2408, 0x2467, 0x2470, 0x2478, 0x247B, 0x256E,
	/* PC CTX 1 */
	0x25C0, 0x25C6, 0x25D0, 0x25D0, 0x25D9, 0x25D9, 0x25E5, 0x25E7,
	/* VFD CTX 1 */
	0x2600, 0x2604, 0x2608, 0x26A9,
	/* SP CTX 1 */+
	0x26C0, 0x26C1, 0x26C4, 0x26E5, 0x26E8, 0x26F8, 0x2700, 0x2706,
	0x270C, 0x2712, 0x2718, 0x2739, 0x2740, 0x2760,
	/* TPL1 CTX 1 */
	0x2780, 0x2782, 0x2784, 0x278F, 0x27A0, 0x27A6,
	/* HLSQ CTXT 1 */
	0x27C0, 0x27DB,
	/* XPU */
	0x2C00, 0x2C01, 0x2C10, 0x2C10, 0x2C12, 0x2C16, 0x2C1D, 0x2C20,
	0x2C28, 0x2C28, 0x2C30, 0x2C30, 0x2C32, 0x2C36, 0x2C40, 0x2C40,
	0x2C50, 0x2C50, 0x2C52, 0x2C56, 0x2C80, 0x2C80, 0x2C94, 0x2C95,
	/* VBIF */
	0x3000, 0x3007, 0x300C, 0x3014, 0x3018, 0x301D, 0x3020, 0x3022,
	0x3024, 0x3026, 0x3028, 0x302A, 0x302C, 0x302D, 0x3030, 0x3031,
	0x3034, 0x3036, 0x3038, 0x3038, 0x303C, 0x303D, 0x3040, 0x3040,
	0x3049, 0x3049, 0x3058, 0x3058, 0x305B, 0x3061, 0x3064, 0x3068,
	0x306C, 0x306D, 0x3080, 0x3088, 0x308B, 0x308C, 0x3090, 0x3094,
	0x3098, 0x3098, 0x309C, 0x309C, 0x30C0, 0x30C0, 0x30C8, 0x30C8,
	0x30D0, 0x30D0, 0x30D8, 0x30D8, 0x30E0, 0x30E0, 0x3100, 0x3100,
	0x3108, 0x3108, 0x3110, 0x3110, 0x3118, 0x3118, 0x3120, 0x3120,
	0x3124, 0x3125, 0x3129, 0x3129, 0x3131, 0x3131, 0x330C, 0x330C,
	0x3310, 0x3310, 0x3400, 0x3401, 0x3410, 0x3410, 0x3412, 0x3416,
	0x341D, 0x3420, 0x3428, 0x3428, 0x3430, 0x3430, 0x3432, 0x3436,
	0x3440, 0x3440, 0x3450, 0x3450, 0x3452, 0x3456, 0x3480, 0x3480,
	0x3494, 0x3495, 0x4000, 0x4000, 0x4002, 0x4002, 0x4004, 0x4004,
	0x4008, 0x400A, 0x400C, 0x400D, 0x400F, 0x4012, 0x4014, 0x4016,
	0x401D, 0x401D, 0x4020, 0x4027, 0x4060, 0x4062, 0x4200, 0x4200,
	0x4300, 0x4300, 0x4400, 0x4400, 0x4500, 0x4500, 0x4800, 0x4802,
	0x480F, 0x480F, 0x4811, 0x4811, 0x4813, 0x4813, 0x4815, 0x4816,
	0x482B, 0x482B, 0x4857, 0x4857, 0x4883, 0x4883, 0x48AF, 0x48AF,
	0x48C5, 0x48C5, 0x48E5, 0x48E5, 0x4905, 0x4905, 0x4925, 0x4925,
	0x4945, 0x4945, 0x4950, 0x4950, 0x495B, 0x495B, 0x4980, 0x498E,
	0x4B00, 0x4B00, 0x4C00, 0x4C00, 0x4D00, 0x4D00, 0x4E00, 0x4E00,
	0x4E80, 0x4E80, 0x4F00, 0x4F00, 0x4F08, 0x4F08, 0x4F10, 0x4F10,
	0x4F18, 0x4F18, 0x4F20, 0x4F20, 0x4F30, 0x4F30, 0x4F60, 0x4F60,
	0x4F80, 0x4F81, 0x4F88, 0x4F89, 0x4FEE, 0x4FEE, 0x4FF3, 0x4FF3,
	0x6000, 0x6001, 0x6008, 0x600F, 0x6014, 0x6016, 0x6018, 0x601B,
	0x61FD, 0x61FD, 0x623C, 0x623C, 0x6380, 0x6380, 0x63A0, 0x63A0,
	0x63C0, 0x63C1, 0x63C8, 0x63C9, 0x63D0, 0x63D4, 0x63D6, 0x63D6,
	0x63EE, 0x63EE, 0x6400, 0x6401, 0x6408, 0x640F, 0x6414, 0x6416,
	0x6418, 0x641B, 0x65FD, 0x65FD, 0x663C, 0x663C, 0x6780, 0x6780,
	0x67A0, 0x67A0, 0x67C0, 0x67C1, 0x67C8, 0x67C9, 0x67D0, 0x67D4,
	0x67D6, 0x67D6, 0x67EE, 0x67EE, 0x6800, 0x6801, 0x6808, 0x680F,
	0x6814, 0x6816, 0x6818, 0x681B, 0x69FD, 0x69FD, 0x6A3C, 0x6A3C,
	0x6B80, 0x6B80, 0x6BA0, 0x6BA0, 0x6BC0, 0x6BC1, 0x6BC8, 0x6BC9,
	0x6BD0, 0x6BD4, 0x6BD6, 0x6BD6, 0x6BEE, 0x6BEE,
};

const unsigned int a4xx_registers_count = ARRAY_SIZE(a4xx_registers) / 2;

/*
 * Define registers for a4xx that contain addresses used by the
 * cp parser logic
 */
const unsigned int a4xx_cp_addr_regs[ADRENO_CP_ADDR_MAX] = {
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_ADDRESS_0,
				A4XX_VSC_PIPE_DATA_ADDRESS_0),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_LENGTH_0,
				A4XX_VSC_PIPE_DATA_LENGTH_0),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_ADDRESS_1,
				A4XX_VSC_PIPE_DATA_ADDRESS_1),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_LENGTH_1,
				A4XX_VSC_PIPE_DATA_LENGTH_1),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_ADDRESS_2,
				A4XX_VSC_PIPE_DATA_ADDRESS_2),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_LENGTH_2,
				A4XX_VSC_PIPE_DATA_LENGTH_2),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_ADDRESS_3,
				A4XX_VSC_PIPE_DATA_ADDRESS_3),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_LENGTH_3,
				A4XX_VSC_PIPE_DATA_LENGTH_3),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_ADDRESS_4,
				A4XX_VSC_PIPE_DATA_ADDRESS_4),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_LENGTH_4,
				A4XX_VSC_PIPE_DATA_LENGTH_4),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_ADDRESS_5,
				A4XX_VSC_PIPE_DATA_ADDRESS_5),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_LENGTH_5,
				A4XX_VSC_PIPE_DATA_LENGTH_5),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_ADDRESS_6,
				A4XX_VSC_PIPE_DATA_ADDRESS_6),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_LENGTH_6,
				A4XX_VSC_PIPE_DATA_LENGTH_6),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_ADDRESS_7,
				A4XX_VSC_PIPE_DATA_ADDRESS_7),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_LENGTH_7,
				A4XX_VSC_PIPE_DATA_LENGTH_7),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_ADDRESS_7,
				A4XX_VSC_PIPE_DATA_ADDRESS_7),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_PIPE_DATA_LENGTH_7,
				A4XX_VSC_PIPE_DATA_LENGTH_7),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_0,
				A4XX_VFD_FETCH_INSTR_1_0),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_1,
				A4XX_VFD_FETCH_INSTR_1_1),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_2,
				A4XX_VFD_FETCH_INSTR_1_2),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_3,
				A4XX_VFD_FETCH_INSTR_1_3),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_4,
				A4XX_VFD_FETCH_INSTR_1_4),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_5,
				A4XX_VFD_FETCH_INSTR_1_5),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_6,
				A4XX_VFD_FETCH_INSTR_1_6),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_7,
				A4XX_VFD_FETCH_INSTR_1_7),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_8,
				A4XX_VFD_FETCH_INSTR_1_8),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_9,
				A4XX_VFD_FETCH_INSTR_1_9),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_10,
				A4XX_VFD_FETCH_INSTR_1_10),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_11,
				A4XX_VFD_FETCH_INSTR_1_11),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_12,
				A4XX_VFD_FETCH_INSTR_1_12),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_13,
				A4XX_VFD_FETCH_INSTR_1_13),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_14,
				A4XX_VFD_FETCH_INSTR_1_14),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_15,
				A4XX_VFD_FETCH_INSTR_1_15),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_16,
				A4XX_VFD_FETCH_INSTR_1_16),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_17,
				A4XX_VFD_FETCH_INSTR_1_17),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_18,
				A4XX_VFD_FETCH_INSTR_1_18),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_19,
				A4XX_VFD_FETCH_INSTR_1_19),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_20,
				A4XX_VFD_FETCH_INSTR_1_20),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_21,
				A4XX_VFD_FETCH_INSTR_1_21),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_22,
				A4XX_VFD_FETCH_INSTR_1_22),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_23,
				A4XX_VFD_FETCH_INSTR_1_23),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_24,
				A4XX_VFD_FETCH_INSTR_1_24),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_25,
				A4XX_VFD_FETCH_INSTR_1_25),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_26,
				A4XX_VFD_FETCH_INSTR_1_26),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_27,
				A4XX_VFD_FETCH_INSTR_1_27),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_28,
				A4XX_VFD_FETCH_INSTR_1_28),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_29,
				A4XX_VFD_FETCH_INSTR_1_29),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_30,
				A4XX_VFD_FETCH_INSTR_1_30),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VFD_FETCH_INSTR_1_31,
				A4XX_VFD_FETCH_INSTR_1_31),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_VSC_SIZE_ADDRESS,
				A4XX_VSC_SIZE_ADDRESS),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_SP_VS_PVT_MEM_ADDR,
				A4XX_SP_VS_PVT_MEM_ADDR),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_SP_FS_PVT_MEM_ADDR,
				A4XX_SP_FS_PVT_MEM_ADDR),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_SP_VS_OBJ_START_REG,
				A4XX_SP_VS_OBJ_START),
	ADRENO_REG_DEFINE(ADRENO_CP_ADDR_SP_FS_OBJ_START_REG,
				A4XX_SP_FS_OBJ_START),
};

static const struct adreno_vbif_data a420_vbif[] = {
	{ A4XX_VBIF_ABIT_SORT, 0x0001001F },
	{ A4XX_VBIF_ABIT_SORT_CONF, 0x000000A4 },
	{ A4XX_VBIF_GATE_OFF_WRREQ_EN, 0x00000001 },
	{ A4XX_VBIF_IN_RD_LIM_CONF0, 0x18181818 },
	{ A4XX_VBIF_IN_RD_LIM_CONF1, 0x00000018 },
	{ A4XX_VBIF_IN_WR_LIM_CONF0, 0x18181818 },
	{ A4XX_VBIF_IN_WR_LIM_CONF1, 0x00000018 },
	{ A4XX_VBIF_ROUND_ROBIN_QOS_ARB, 0x00000003 },
	{0, 0},
};

const struct adreno_vbif_platform a4xx_vbif_platforms[] = {
	{ adreno_is_a420, a420_vbif },
};

static void a4xx_start(struct adreno_device *adreno_dev)
{
	struct kgsl_device *device = &adreno_dev->dev;

	adreno_vbif_start(device, a4xx_vbif_platforms,
			ARRAY_SIZE(a4xx_vbif_platforms));
	/* Make all blocks contribute to the GPU BUSY perf counter */
	kgsl_regwrite(device, A4XX_RBBM_GPU_BUSY_MASKED, 0xFFFFFFFF);

	/* Tune the hystersis counters for SP and CP idle detection */
	kgsl_regwrite(device, A4XX_RBBM_SP_HYST_CNT, 0x10);
	kgsl_regwrite(device, A4XX_RBBM_WAIT_IDLE_CLOCKS_CTL, 0x10);

	/*
	 * Enable the RBBM error reporting bits.  This lets us get
	 * useful information on failure
	 */

	kgsl_regwrite(device, A4XX_RBBM_AHB_CTL0, 0x00000001);

	/* Enable AHB error reporting */
	kgsl_regwrite(device, A4XX_RBBM_AHB_CTL1, 0xA6FFFFFF);

	/* Turn on the power counters */
	kgsl_regwrite(device, A4XX_RBBM_RBBM_CTL, 0x00000030);

	/*
	 * Turn on hang detection - this spews a lot of useful information
	 * into the RBBM registers on a hang
	 */

	kgsl_regwrite(device, A4XX_RBBM_INTERFACE_HANG_INT_CTL,
			(1 << 16) | 0xFFF);

	/* Set the OCMEM base address for A4XX */
	kgsl_regwrite(device, A4XX_RB_GMEM_BASE_ADDR,
			(unsigned int)(adreno_dev->ocmem_base >> 14));

	/* Turn on performance counters */
	kgsl_regwrite(device, A4XX_RBBM_PERFCTR_CTL, 0x01);
	/* Turn on the GPU busy counter and let it run free */
	adreno_dev->gpu_cycles = 0;

	/* Disable L2 bypass to avoid UCHE out of bounds errors */
	kgsl_regwrite(device, UCHE_TRAP_BASE_LO, 0xffff0000);
	kgsl_regwrite(device, UCHE_TRAP_BASE_HI, 0xffff0000);

}

int a4xx_perfcounter_enable_vbif(struct kgsl_device *device,
				unsigned int counter,
				unsigned int countable)
{
	struct adreno_device *adreno_dev = ADRENO_DEVICE(device);
	struct adreno_perfcounters *counters = adreno_dev->gpudev->perfcounters;
	struct adreno_perfcount_register *reg;

	if (counter > 3 || countable > A4XX_VBIF_PERF_CNT_SEL_MASK)
		return -EINVAL;

	reg = &counters->groups[KGSL_PERFCOUNTER_GROUP_VBIF].regs[counter];
	kgsl_regwrite(device, reg->select - A4XX_VBIF_PERF_CLR_REG_SEL_OFF, 1);
	kgsl_regwrite(device, reg->select - A4XX_VBIF_PERF_CLR_REG_SEL_OFF, 0);
	kgsl_regwrite(device, reg->select,
			countable & A4XX_VBIF_PERF_CNT_SEL_MASK);
	/* enable reg is 8 DWORDS before select reg */
	kgsl_regwrite(device, reg->select - A4XX_VBIF_PERF_EN_REG_SEL_OFF, 1);
	return 0;
}

uint64_t a4xx_perfcounter_read_vbif(struct kgsl_device *device,
					unsigned int counter)
{
	struct adreno_device *adreno_dev = ADRENO_DEVICE(device);
	struct adreno_perfcounters *counters = adreno_dev->gpudev->perfcounters;
	struct adreno_perfcount_register *reg;
	unsigned int lo = 0, hi = 0;

	if (counter > 3)
		return 0;

	reg = &counters->groups[KGSL_PERFCOUNTER_GROUP_VBIF].regs[counter];

	kgsl_regread(device, reg->offset, &lo);
	/* HI offset is 8 DWORDS after the LOW offset */
	kgsl_regread(device, reg->offset + A4XX_VBIF_PERF_HIGH_REG_LOW_OFF,
			&hi);

	return (((uint64_t) hi) << 32) | lo;
}

int a4xx_perfcounter_enable_vbif_pwr(struct kgsl_device *device,
					unsigned int counter)
{
	struct adreno_device *adreno_dev = ADRENO_DEVICE(device);
	struct adreno_perfcounters *counters = adreno_dev->gpudev->perfcounters;
	struct adreno_perfcount_register *reg;

	if (counter > 3)
		return -EINVAL;

	reg = &counters->groups[KGSL_PERFCOUNTER_GROUP_VBIF_PWR].regs[counter];

	/*
	 * since power registers dont have select register, the enable
	 * reg is stored here
	 */
	kgsl_regwrite(device, reg->select + A4XX_VBIF_PERF_PWR_CLR_REG_EN_OFF,
			1);
	kgsl_regwrite(device, reg->select + A4XX_VBIF_PERF_PWR_CLR_REG_EN_OFF,
			0);
	kgsl_regwrite(device, reg->select, 1);
	return 0;
}

uint64_t a4xx_perfcounter_read_vbif_pwr(struct kgsl_device *device,
						unsigned int counter)
{
	struct adreno_device *adreno_dev = ADRENO_DEVICE(device);
	struct adreno_perfcounters *counters = adreno_dev->gpudev->perfcounters;
	struct adreno_perfcount_register *reg;
	unsigned int lo = 0, hi = 0;

	 if (counter > 3)
		return 0;

	reg = &counters->groups[KGSL_PERFCOUNTER_GROUP_VBIF_PWR].regs[counter];

	kgsl_regread(device, reg->offset, &lo);
	/* HI offset is 8 DWORDS after the LOW offset */
	kgsl_regread(device, reg->offset + A4XX_VBIF_PERF_PWR_HIGH_REG_LOW_OFF,
			&hi);

	return (((uint64_t) hi) << 32) | lo;
}

/* Register offset defines for A4XX, in order of enum adreno_regs */
static unsigned int a4xx_register_offsets[ADRENO_REG_REGISTER_MAX] = {
	ADRENO_REG_DEFINE(ADRENO_REG_CP_DEBUG, A4XX_CP_DEBUG),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_ME_RAM_WADDR, A4XX_CP_ME_RAM_WADDR),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_ME_RAM_DATA, A4XX_CP_ME_RAM_DATA),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_PFP_UCODE_DATA, A4XX_CP_PFP_UCODE_DATA),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_PFP_UCODE_ADDR, A4XX_CP_PFP_UCODE_ADDR),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_WFI_PEND_CTR, A4XX_CP_WFI_PEND_CTR),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_RB_BASE, A4XX_CP_RB_BASE),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_RB_RPTR_ADDR, A4XX_CP_RB_RPTR_ADDR),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_RB_RPTR, A4XX_CP_RB_RPTR),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_RB_WPTR, A4XX_CP_RB_WPTR),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_PROTECT_CTRL, A4XX_CP_PROTECT_CTRL),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_ME_CNTL, A4XX_CP_ME_CNTL),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_RB_CNTL, A4XX_CP_RB_CNTL),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_IB1_BASE, A4XX_CP_IB1_BASE),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_IB1_BUFSZ, A4XX_CP_IB1_BUFSZ),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_IB2_BASE, A4XX_CP_IB2_BASE),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_IB2_BUFSZ, A4XX_CP_IB2_BUFSZ),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_TIMESTAMP, A4XX_CP_SCRATCH_REG0),
	ADRENO_REG_DEFINE(ADRENO_REG_CP_ME_RAM_RADDR, A4XX_CP_ME_RAM_RADDR),
	ADRENO_REG_DEFINE(ADRENO_REG_SCRATCH_ADDR, A4XX_CP_SCRATCH_ADDR),
	ADRENO_REG_DEFINE(ADRENO_REG_SCRATCH_UMSK, A4XX_CP_SCRATCH_UMASK),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_STATUS, A4XX_RBBM_STATUS),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_PERFCTR_CTL, A4XX_RBBM_PERFCTR_CTL),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_PERFCTR_LOAD_CMD0,
					A4XX_RBBM_PERFCTR_LOAD_CMD0),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_PERFCTR_LOAD_CMD1,
					A4XX_RBBM_PERFCTR_LOAD_CMD1),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_PERFCTR_LOAD_CMD2,
				A4XX_RBBM_PERFCTR_LOAD_CMD2),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_PERFCTR_PWR_1_LO,
					A4XX_RBBM_PERFCTR_PWR_1_LO),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_INT_0_MASK, A4XX_RBBM_INT_0_MASK),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_INT_0_STATUS, A4XX_RBBM_INT_0_STATUS),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_AHB_ERROR_STATUS,
					A4XX_RBBM_AHB_ERROR_STATUS),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_AHB_CMD, A4XX_RBBM_AHB_CMD),
	ADRENO_REG_DEFINE(ADRENO_REG_VPC_DEBUG_RAM_SEL,
					A4XX_VPC_DEBUG_RAM_SEL),
	ADRENO_REG_DEFINE(ADRENO_REG_VPC_DEBUG_RAM_READ,
					A4XX_VPC_DEBUG_RAM_READ),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_INT_CLEAR_CMD,
				A4XX_RBBM_INT_CLEAR_CMD),
	ADRENO_REG_DEFINE(ADRENO_REG_VSC_PIPE_DATA_ADDRESS_0,
				A4XX_VSC_PIPE_DATA_ADDRESS_0),
	ADRENO_REG_DEFINE(ADRENO_REG_VSC_PIPE_DATA_LENGTH_7,
					A4XX_VSC_PIPE_DATA_LENGTH_7),
	ADRENO_REG_DEFINE(ADRENO_REG_VSC_SIZE_ADDRESS, A4XX_VSC_SIZE_ADDRESS),
	ADRENO_REG_DEFINE(ADRENO_REG_VFD_CONTROL_0, A4XX_VFD_CONTROL_0),
	ADRENO_REG_DEFINE(ADRENO_REG_VFD_FETCH_INSTR_0_0,
					A4XX_VFD_FETCH_INSTR_0_0),
	ADRENO_REG_DEFINE(ADRENO_REG_VFD_FETCH_INSTR_1_F,
					A4XX_VFD_FETCH_INSTR_1_31),
	ADRENO_REG_DEFINE(ADRENO_REG_SP_VS_PVT_MEM_ADDR_REG,
				A4XX_SP_VS_PVT_MEM_ADDR),
	ADRENO_REG_DEFINE(ADRENO_REG_SP_FS_PVT_MEM_ADDR_REG,
				A4XX_SP_FS_PVT_MEM_ADDR),
	ADRENO_REG_DEFINE(ADRENO_REG_SP_VS_OBJ_START_REG,
				A4XX_SP_VS_OBJ_START),
	ADRENO_REG_DEFINE(ADRENO_REG_SP_FS_OBJ_START_REG,
				A4XX_SP_FS_OBJ_START),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_RBBM_CTL, A4XX_RBBM_RBBM_CTL),
	ADRENO_REG_DEFINE(ADRENO_REG_RBBM_SW_RESET_CMD, A4XX_RBBM_SW_RESET_CMD),
};

const struct adreno_reg_offsets a4xx_reg_offsets = {
	.offsets = a4xx_register_offsets,
	.offset_0 = ADRENO_REG_REGISTER_MAX,
};

static struct adreno_perfcount_register a4xx_perfcounters_cp[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_CP_0_LO,
		0, A4XX_CP_PERFCTR_CP_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_CP_1_LO,
		1, A4XX_CP_PERFCTR_CP_SEL_1 },
};

static struct adreno_perfcount_register a4xx_perfcounters_rbbm[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RBBM_0_LO,
		8, A4XX_RBBM_PERFCTR_RBBM_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RBBM_1_LO,
		9, A4XX_RBBM_PERFCTR_RBBM_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RBBM_2_LO,
		10, A4XX_RBBM_PERFCTR_RBBM_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RBBM_3_LO,
		11, A4XX_RBBM_PERFCTR_RBBM_SEL_3 },
};

static struct adreno_perfcount_register a4xx_perfcounters_pc[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_PC_0_LO,
		12, A4XX_PC_PERFCTR_PC_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_PC_1_LO,
		13, A4XX_PC_PERFCTR_PC_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_PC_2_LO,
		14, A4XX_PC_PERFCTR_PC_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_PC_3_LO,
		15, A4XX_PC_PERFCTR_PC_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_PC_4_LO,
		16, A4XX_PC_PERFCTR_PC_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_PC_5_LO,
		17, A4XX_PC_PERFCTR_PC_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_PC_6_LO,
		18, A4XX_PC_PERFCTR_PC_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_PC_7_LO,
		19, A4XX_PC_PERFCTR_PC_SEL_7 },
};

static struct adreno_perfcount_register a4xx_perfcounters_vfd[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_VFD_0_LO,
		20, A4XX_VFD_PERFCTR_VFD_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_VFD_1_LO,
		21, A4XX_VFD_PERFCTR_VFD_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_VFD_2_LO,
		22, A4XX_VFD_PERFCTR_VFD_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_VFD_3_LO,
		23, A4XX_VFD_PERFCTR_VFD_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_VFD_4_LO,
		24, A4XX_VFD_PERFCTR_VFD_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_VFD_5_LO,
		25, A4XX_VFD_PERFCTR_VFD_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_VFD_6_LO,
		26, A4XX_VFD_PERFCTR_VFD_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_VFD_7_LO,
		27, A4XX_VFD_PERFCTR_VFD_SEL_7 },
};

static struct adreno_perfcount_register a4xx_perfcounters_hlsq[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_HLSQ_0_LO,
		28, A4XX_HLSQ_PERFCTR_HLSQ_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_HLSQ_1_LO,
		29, A4XX_HLSQ_PERFCTR_HLSQ_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_HLSQ_2_LO,
		30, A4XX_HLSQ_PERFCTR_HLSQ_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_HLSQ_3_LO,
		31, A4XX_HLSQ_PERFCTR_HLSQ_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_HLSQ_4_LO,
		32, A4XX_HLSQ_PERFCTR_HLSQ_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_HLSQ_5_LO,
		33, A4XX_HLSQ_PERFCTR_HLSQ_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_HLSQ_6_LO,
		34, A4XX_HLSQ_PERFCTR_HLSQ_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_HLSQ_7_LO,
		35, A4XX_HLSQ_PERFCTR_HLSQ_SEL_7 },
};

static struct adreno_perfcount_register a4xx_perfcounters_vpc[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_VPC_0_LO,
		36, A4XX_VPC_PERFCTR_VPC_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_VPC_1_LO,
		37, A4XX_VPC_PERFCTR_VPC_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_VPC_2_LO,
		38, A4XX_VPC_PERFCTR_VPC_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_VPC_3_LO,
		39, A4XX_VPC_PERFCTR_VPC_SEL_3 },
};

static struct adreno_perfcount_register a4xx_perfcounters_ccu[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_CCU_0_LO,
		40, A4XX_RB_PERFCTR_CCU_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_CCU_1_LO,
		41, A4XX_RB_PERFCTR_CCU_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_CCU_2_LO,
		42, A4XX_RB_PERFCTR_CCU_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_CCU_3_LO,
		43, A4XX_RB_PERFCTR_CCU_SEL_3 },
};

static struct adreno_perfcount_register a4xx_perfcounters_tse[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_TSE_0_LO,
		44, A4XX_GRAS_PERFCTR_TSE_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_TSE_1_LO,
		45, A4XX_GRAS_PERFCTR_TSE_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_TSE_2_LO,
		46, A4XX_GRAS_PERFCTR_TSE_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_TSE_3_LO,
		47, A4XX_GRAS_PERFCTR_TSE_SEL_3 },
};


static struct adreno_perfcount_register a4xx_perfcounters_ras[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RAS_0_LO,
		48, A4XX_GRAS_PERFCTR_RAS_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RAS_1_LO,
		49, A4XX_GRAS_PERFCTR_RAS_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RAS_2_LO,
		50, A4XX_GRAS_PERFCTR_RAS_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RAS_3_LO,
		51, A4XX_GRAS_PERFCTR_RAS_SEL_3 },
};

static struct adreno_perfcount_register a4xx_perfcounters_uche[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_UCHE_0_LO,
		52, A4XX_UCHE_PERFCTR_UCHE_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_UCHE_1_LO,
		53, A4XX_UCHE_PERFCTR_UCHE_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_UCHE_2_LO,
		54, A4XX_UCHE_PERFCTR_UCHE_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_UCHE_3_LO,
		55, A4XX_UCHE_PERFCTR_UCHE_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_UCHE_4_LO,
		56, A4XX_UCHE_PERFCTR_UCHE_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_UCHE_5_LO,
		57, A4XX_UCHE_PERFCTR_UCHE_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_UCHE_6_LO,
		58, A4XX_UCHE_PERFCTR_UCHE_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_UCHE_7_LO,
		59, A4XX_UCHE_PERFCTR_UCHE_SEL_7 },
};

static struct adreno_perfcount_register a4xx_perfcounters_tp[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_TP_0_LO,
		60, A4XX_TPL1_PERFCTR_TP_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_TP_1_LO,
		61, A4XX_TPL1_PERFCTR_TP_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_TP_2_LO,
		62, A4XX_TPL1_PERFCTR_TP_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_TP_3_LO,
		63, A4XX_TPL1_PERFCTR_TP_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_TP_4_LO,
		64, A4XX_TPL1_PERFCTR_TP_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_TP_5_LO,
		65, A4XX_TPL1_PERFCTR_TP_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_TP_6_LO,
		66, A4XX_TPL1_PERFCTR_TP_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_TP_7_LO,
		67, A4XX_TPL1_PERFCTR_TP_SEL_7 },
};

static struct adreno_perfcount_register a4xx_perfcounters_sp[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_SP_0_LO,
		68, A4XX_SP_PERFCTR_SP_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_SP_1_LO,
		69, A4XX_SP_PERFCTR_SP_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_SP_2_LO,
		70, A4XX_SP_PERFCTR_SP_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_SP_3_LO,
		71, A4XX_SP_PERFCTR_SP_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_SP_4_LO,
		72, A4XX_SP_PERFCTR_SP_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_SP_5_LO,
		73, A4XX_SP_PERFCTR_SP_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_SP_6_LO,
		74, A4XX_SP_PERFCTR_SP_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_SP_7_LO,
		75, A4XX_SP_PERFCTR_SP_SEL_7 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_SP_8_LO,
		76, A4XX_SP_PERFCTR_SP_SEL_8 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_SP_9_LO,
		77, A4XX_SP_PERFCTR_SP_SEL_9 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_SP_10_LO,
		78, A4XX_SP_PERFCTR_SP_SEL_10 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_SP_11_LO,
		79, A4XX_SP_PERFCTR_SP_SEL_11 },
};

static struct adreno_perfcount_register a4xx_perfcounters_rb[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RB_0_LO,
		80, A4XX_RB_PERFCTR_RB_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RB_1_LO,
		81, A4XX_RB_PERFCTR_RB_SEL_1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RB_2_LO,
		82, A4XX_RB_PERFCTR_RB_SEL_2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RB_3_LO,
		83, A4XX_RB_PERFCTR_RB_SEL_3 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RB_4_LO,
		84, A4XX_RB_PERFCTR_RB_SEL_4 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RB_5_LO,
		85, A4XX_RB_PERFCTR_RB_SEL_5 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RB_6_LO,
		86, A4XX_RB_PERFCTR_RB_SEL_6 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_RB_7_LO,
		87, A4XX_RB_PERFCTR_RB_SEL_7 },
};

static struct adreno_perfcount_register a4xx_perfcounters_vsc[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_VSC_0_LO,
		88, A4XX_VSC_PERFCTR_VSC_SEL_0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_VSC_1_LO,
		89, A4XX_VSC_PERFCTR_VSC_SEL_1 },
};

static struct adreno_perfcount_register a4xx_perfcounters_pwr[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_PWR_0_LO,
		-1, 0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_RBBM_PERFCTR_PWR_1_LO,
		-1, 0},
};

static struct adreno_perfcount_register a4xx_perfcounters_vbif[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_VBIF_PERF_CNT_LOW0,
		-1, A4XX_VBIF_PERF_CNT_SEL0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_VBIF_PERF_CNT_LOW1,
		-1, A4XX_VBIF_PERF_CNT_SEL1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_VBIF_PERF_CNT_LOW2,
		-1, A4XX_VBIF_PERF_CNT_SEL2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_VBIF_PERF_CNT_LOW3,
		-1, A4XX_VBIF_PERF_CNT_SEL3 },
};

static struct adreno_perfcount_register a4xx_perfcounters_vbif_pwr[] = {
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_VBIF_PERF_PWR_CNT_LOW0,
		-1, A4XX_VBIF_PERF_PWR_CNT_EN0 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_VBIF_PERF_PWR_CNT_LOW1,
		-1, A4XX_VBIF_PERF_PWR_CNT_EN1 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_VBIF_PERF_PWR_CNT_LOW2,
		-1, A4XX_VBIF_PERF_PWR_CNT_EN2 },
	{ KGSL_PERFCOUNTER_NOT_USED, 0, 0, A4XX_VBIF_PERF_PWR_CNT_LOW3,
		-1, A4XX_VBIF_PERF_PWR_CNT_EN3 },
};

static struct adreno_perfcount_group a4xx_perfcounter_groups
				[KGSL_PERFCOUNTER_GROUP_MAX] = {
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, cp, CP),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, rbbm, RBBM),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, pc, PC),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, vfd, VFD),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, hlsq, HLSQ),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, vpc, VPC),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, ccu, CCU),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, tse, TSE),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, ras, RAS),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, uche, UCHE),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, tp, TP),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, sp, SP),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, rb, RB),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, vsc, VSC),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, pwr, PWR),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, vbif, VBIF),
	ADRENO_PERFCOUNTER_GROUP_OFF(a4xx, vbif_pwr, VBIF_PWR),
};

static struct adreno_perfcounters a4xx_perfcounters = {
	a4xx_perfcounter_groups,
	ARRAY_SIZE(a4xx_perfcounter_groups),
};

/*
 * On A4xx a number of perfcounters are un-usable. The following defines the
 * array of countables that do not work and should not be used
 */
static const unsigned int pc_invalid_countables[] = {
	PC_INSTANCES, PC_VERTEX_HITS, PC_GENERATED_FIBERS, PC_GENERATED_WAVES,
};

static unsigned int vfd_invalid_countables[] = {
	VFD_VPC_BYPASS_TRANS, VFD_UPPER_SHADER_FIBERS, VFD_LOWER_SHADER_FIBERS,
};

static const unsigned int hlsq_invalid_countables[] = {
	HLSQ_SP_VS_STAGE_CONSTANT, HLSQ_SP_VS_STAGE_INSTRUCTIONS,
	HLSQ_SP_FS_STAGE_CONSTANT, HLSQ_SP_FS_STAGE_INSTRUCTIONS,
	HLSQ_FS_STAGE_16_WAVES, HLSQ_FS_STAGE_32_WAVES, HLSQ_FS_STAGE_64_WAVES,
	HLSQ_VS_STAGE_16_WAVES, HLSQ_VS_STAGE_32_WAVES,
};

static const unsigned int uche_invalid_countables[] = {
	UCHE_READ_REQUESTS_MARB, UCHE_READ_REQUESTS_SP,
	UCHE_WRITE_REQUESTS_MARB, UCHE_WRITE_REQUESTS_SP,
	UCHE_WRITE_REQUESTS_VPC
};

static const unsigned int tp_invalid_countables[] = {
	TP_OUTPUT_TEXELS_POINT, TP_OUTPUT_TEXELS_BILINEAR, TP_OUTPUT_TEXELS_MIP,
	TP_OUTPUT_TEXELS_ANISO, TP_OUTPUT_TEXELS_OPS16, TP_OUTPUT_TEXELS_OPS32,
	TP_ZERO_LOD, TP_LATENCY, TP_LATENCY_TRANS,
};

static const unsigned int sp_invalid_countables[] = {
	SP_FS_STAGE_BARY_INSTRUCTIONS,
};

static const unsigned int rb_invalid_countables[] = {
	RB_VALID_SAMPLES, RB_Z_FAIL, RB_S_FAIL,
};

static const unsigned int ccu_invalid_countables[] = {
	CCU_VBIF_STALL, CCU_VBIF_LATENCY_CYCLES, CCU_VBIF_LATENCY_SAMPLES,
	CCU_Z_READ, CCU_Z_WRITE, CCU_C_READ, CCU_C_WRITE,
};

static const struct adreno_invalid_countables
	a4xx_perfctr_invalid_countables[KGSL_PERFCOUNTER_GROUP_MAX] = {
	ADRENO_PERFCOUNTER_INVALID_COUNTABLE(pc, PC),
	ADRENO_PERFCOUNTER_INVALID_COUNTABLE(vfd, VFD),
	ADRENO_PERFCOUNTER_INVALID_COUNTABLE(hlsq, HLSQ),
	ADRENO_PERFCOUNTER_INVALID_COUNTABLE(tp, TP),
	ADRENO_PERFCOUNTER_INVALID_COUNTABLE(sp, SP),
	ADRENO_PERFCOUNTER_INVALID_COUNTABLE(rb, RB),
	ADRENO_PERFCOUNTER_INVALID_COUNTABLE(ccu, CCU),
	ADRENO_PERFCOUNTER_INVALID_COUNTABLE(uche, UCHE),
};

struct adreno_gpudev adreno_a4xx_gpudev = {
	.reg_offsets = &a4xx_reg_offsets,
	.perfcounters = &a4xx_perfcounters,

	.rb_init = a3xx_rb_init,
	.irq_control = a3xx_irq_control,
	.irq_handler = a3xx_irq_handler,
	.irq_pending = a3xx_irq_pending,
	.busy_cycles = a3xx_busy_cycles,
	.start = a4xx_start,
	.perfcounter_enable = a3xx_perfcounter_enable,
	.perfcounter_read = a3xx_perfcounter_read,
	.invalid_countables = a4xx_perfctr_invalid_countables,
	.soft_reset = a3xx_soft_reset,
};
