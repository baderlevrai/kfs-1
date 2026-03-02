#include "kernel.h"

void	hello(void) {
	terminal_wstr("   _____ ________\n");
	terminal_wstr("  /  |  |\\_____  \\\n");
	terminal_wstr(" /   |  |_/  ____/\n");
	terminal_wstr("/    ^   /       \\\n");
	terminal_wstr("\\____   |\\_______ \\\n");
	terminal_wstr("     |__|        \\/\n");
}

void kernel_main(void)
{
	terminal_initialize();

	terminal_wstr("Hello, kernel World!\n");
	terminal_wstr("This is a simple kernel written in C.\n");

	hello();

  printk("Printk example %d\n", 42);
  printk("Screen address: %p", VGA_MEMORY);
  kbd_init();

	kbd_handler();

}
