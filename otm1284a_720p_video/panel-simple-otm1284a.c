// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode otm1284a_mode = {
	.clock = (720 + 92 + 12 + 64) * (1280 + 10 + 5 + 13) * 60 / 1000,
	.hdisplay = 720,
	.hsync_start = 720 + 92,
	.hsync_end = 720 + 92 + 12,
	.htotal = 720 + 92 + 12 + 64,
	.vdisplay = 1280,
	.vsync_start = 1280 + 10,
	.vsync_end = 1280 + 10 + 5,
	.vtotal = 1280 + 10 + 5 + 13,
	.width_mm = 68,
	.height_mm = 121,
};

static const struct panel_desc_dsi otm1284a = {
	.desc = {
		.modes = &otm1284a_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 68,
			.height = 121,
		},
	},
	.flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
		 MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_EOT_PACKET |
		 MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM,
	.format = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
};
