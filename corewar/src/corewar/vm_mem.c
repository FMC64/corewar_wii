/*
** EPITECH PROJECT, 2018
** ಠωಠ
** File description:
** headaaaas
*/

#include "headers.h"

int32_t vm_mem_ref_read(vm_mem_ref_t ref)
{
    switch (ref.type) {
    case VM_MEM_REF_MAIN:
        return *((int32_t*)ref.ptr);
    case VM_MEM_REF_VM_ABS:
        if (ref.is_short)
            return vm_read_uint16(ref.ptr);
        else
            return vm_read_uint32(ref.ptr);
    case VM_MEM_REF_VM_REL:
        if (ref.is_short)
            return vm_read_uint16(_vm.prog_running->op.pc + ref.ptr % PTR_RANGE);
        else
            return vm_read_uint32(_vm.prog_running->op.pc + ref.ptr % PTR_RANGE);
    default:
        return 0;
    }
}

void vm_mem_ref_write(vm_mem_ref_t ref, int32_t value)
{
    switch (ref.type) {
    case VM_MEM_REF_MAIN:
        *((int32_t*)ref.ptr) = value;
        break;
    case VM_MEM_REF_VM_ABS:
        if (ref.is_short)
            return vm_write_uint16(ref.ptr, value);
        else
            return vm_write_uint32(ref.ptr, value);
    case VM_MEM_REF_VM_REL:
        if (ref.is_short)
            return vm_write_uint16(
            _vm.prog_running->op.pc + ref.ptr % PTR_RANGE, value);
        else
            return vm_write_uint32(
            _vm.prog_running->op.pc + ref.ptr % PTR_RANGE, value);
    }
}

int32_t vm_mem_ref_read_rel(vm_mem_ref_t ref, int32_t offset)
{
    ref.ptr = (ssize_t)ref.ptr + offset;
    return vm_mem_ref_read(ref);
}

void vm_mem_ref_write_rel(vm_mem_ref_t ref, int32_t offset, int32_t value)
{
    ref.ptr = (ssize_t)ref.ptr + offset;
    vm_mem_ref_write(ref, value);
}
