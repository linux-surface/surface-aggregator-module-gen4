// SPDX-License-Identifier: GPL-2.0-or-later

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/acpi.h>
#include <linux/platform_device.h>


static int sb1_dgpu_sw_probe(struct platform_device *pdev)
{
	return 0;	// TODO
}

static int sb1_dgpu_sw_remove(struct platform_device *pdev)
{
	return 0;	// TODO
}

/*
 * The dGPU power seems to be actually handled by MSHW0040. However, that is
 * also the power-/volume-button device with a mainline driver. So let's use
 * MSHW0041 instead for now, which seems to be the LTCH (latch/DTX) device.
 */
static const struct acpi_device_id sb1_dgpu_sw_match[] = {
	{ "MSHW0041", },
	{ },
};
MODULE_DEVICE_TABLE(acpi, sb1_dgpu_sw_match);

static struct platform_driver sb1_dgpu_sw = {
	.probe = sb1_dgpu_sw_probe,
	.remove = sb1_dgpu_sw_remove,
	.driver = {
		.name = "surface_sam_sid",
		.acpi_match_table = sb1_dgpu_sw_match,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	},
};
module_platform_driver(sb1_dgpu_sw);

MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("Discrete GPU Power-Switch for Surface Book 1");
MODULE_LICENSE("GPL");
