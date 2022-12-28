#ifndef SLOT_CLASS_H
#define SLOT_CLASS_H

#include <godot_cpp/core/binder_common.hpp>
#include "item.h"

using namespace godot;

class Slot : public RefCounted {
    GDCLASS(Slot, RefCounted);

private:
    Ref<Item> item;
    int amount = 0;

protected:
	static void _bind_methods();

public:
	Slot();
	~Slot();
    void set_item(const Ref<Item> &new_item);
    Ref<Item> get_item() const;
    void set_amount(const int &new_amount);
    int get_amount() const;
    bool is_empty() const;
    int add(const Ref<Item> &item, const int &amount);
    int remove(const Ref<Item> &item, const int &amount);
};

#endif