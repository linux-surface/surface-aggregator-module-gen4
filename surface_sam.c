#include <linux/acpi.h>
#include <linux/kernel.h>


static void print_acpi_name(const char *fmt, acpi_handle handle) {
    struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };

    acpi_get_name(handle, ACPI_FULL_PATHNAME, &buffer);
    printk(fmt, (char *)buffer.pointer);
    kfree(buffer.pointer);
}


static acpi_status surface_sam_opreg_handler(u32 function, acpi_physical_address address,
                                             u32 bit_width, u64 *value, void *handler_context,
                                             void *region_context)
{
    u8 *buf = (u8 *)value;

    printk(KERN_INFO "surface_sam: handler called\n");
    printk(KERN_INFO "surface_sam:   function: %u\n", function);
    printk(KERN_INFO "surface_sam:   address: %llu\n", address);
    printk(KERN_INFO "surface_sam:   bit_width: %u\n", bit_width);
    printk(KERN_INFO "surface_sam:   value: [%02x, %02x, %02x, %02x, ...]\n", buf[0], buf[1], buf[2], buf[3]);

    return 0;
}


static int surface_sam_add(struct acpi_device *device)
{
    struct acpi_device *parent = device->parent;
    int status;

    print_acpi_name(KERN_INFO "surface_sam: device-name: %s\n", device->handle);
    print_acpi_name(KERN_INFO "surface_sam: parent-name: %s\n", parent->handle);

    status = acpi_install_address_space_handler(parent->handle, ACPI_ADR_SPACE_GSBUS,
            &surface_sam_opreg_handler, NULL, NULL);

    if (status) {
        printk(KERN_ERR "surface_sam: could not install address space handler: %d\n", status);
        return -EFAULT;
    }

    return 0;
}

static int surface_sam_remove(struct acpi_device *device)
{
    struct acpi_device *parent = device->parent;
    int status;

    status = acpi_remove_address_space_handler(parent->handle, ACPI_ADR_SPACE_GSBUS,
            &surface_sam_opreg_handler);

    if (status) {
        printk(KERN_ERR "surface_sam: could not remove address space handler: %d\n", status);
        return -EFAULT;
    }

    return 0;
}


static const struct acpi_device_id surface_sam_ids[] = {
    {"MSHW0030", 0},
    {"", 0},
};
MODULE_DEVICE_TABLE(acpi, surface_sam_ids);

static struct acpi_driver surface_sam_driver = {
    .name = "Surface SAM Driver",
    .ids = surface_sam_ids,
    .ops = {
        .add = surface_sam_add,
        .remove = surface_sam_remove,
    },
    .owner = THIS_MODULE,
};

module_acpi_driver(surface_sam_driver);

MODULE_AUTHOR("Maximilian Luz");
MODULE_DESCRIPTION("ACPI/Platform Drivers for Surface SAM controller");
MODULE_LICENSE("GPL v2");
