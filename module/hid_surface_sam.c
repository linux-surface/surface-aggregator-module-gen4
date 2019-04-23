#include <linux/module.h>
#include <linux/hid.h>


static int sam_raw_event(struct hid_device *hdev, struct hid_report *report, u8 *data, int size)
{
	hid_info(hdev, "sam_raw_event\n");
	hid_info(hdev, "  report: id=%u, type=%u, application=%u\n", report->id, report->type, report->application);
	print_hex_dump(KERN_INFO, "data: ", DUMP_PREFIX_OFFSET, 16, 1, data, size, false);

	return 0;
}

static int sam_event(struct hid_device *hdev, struct hid_field *field, struct hid_usage *usage, __s32 value)
{
	hid_info(hdev, "sam_event\n");
	hid_info(hdev, " field: physical=%u, logical=%u, application=%u\n", field->physical, field->logical, field->application);
	hid_info(hdev, " usage: hid=%u, c_idx=%u, u_idx=%u\n", usage->hid, usage->collection_index, usage->usage_index);
	hid_info(hdev, " value: %d\n", value);
	return 1;
}

static void sam_report(struct hid_device *hdev, struct hid_report *report)
{
	hid_info(hdev, "sam_report: \n");
	hid_info(hdev, "  report: id=%u, type=%u, application=%u\n", report->id, report->type, report->application);
}


static int sam_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	hid_info(hdev, "sam_probe: device: %s, bus: %d\n", hdev->name, hdev->bus);
	return 0;
}

static void sam_remove(struct hid_device *hdev)
{
	hid_info(hdev, "sam_remove: device: %s, bus: %d\n", hdev->name, hdev->bus);
}


static const struct hid_device_id ms_surface_sam_ids[] = {
	{ HID_I2C_DEVICE(0x045E, 0x0914), 0 },
	{ },
};

MODULE_DEVICE_TABLE(hid, ms_surface_sam_ids);


struct hid_driver ms_surface_sam_driver = {
	.name             = "hid_surface_sam",
	.id_table         = ms_surface_sam_ids,

	.probe            = sam_probe,
	.remove           = sam_remove,
	.raw_event        = sam_raw_event,
	.event            = sam_event,
	.report           = sam_report,
};

module_hid_driver(ms_surface_sam_driver);

MODULE_AUTHOR("Maximilian Luz");
MODULE_DESCRIPTION("Driver for Surface Aggregator Module over HID");
MODULE_LICENSE("GPL v2");
