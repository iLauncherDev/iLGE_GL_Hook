#include <gl_hook.h>

pvoid get_proc_address(const char *name)
{
    uintptr_t address_value = 0;
    if (main_hook.get_proc_address_f)
        address_value = (uintptr_t)main_hook.get_proc_address_f(main_hook.context, name);

    if (address_value == (uintptr_t)-1 || address_value <= 3)
        address_value = 0;

    return (pvoid)address_value;
}

void *get_first_proc_address_on_proc_table(const char **proc_list, int proc_count)
{
    for (int i = 0; i < proc_count; i++)
    {
        const char *proc = proc_list[i];

        void *address = get_proc_address(proc);
        if (address)
            return address;
    }

    return NULL;
}
