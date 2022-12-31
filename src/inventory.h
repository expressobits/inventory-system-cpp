#ifndef INVENTORY_CLASS_H
#define INVENTORY_CLASS_H

// We don't need windows.h in this example plugin but many others do, and it can
// lead to annoying situations due to the ton of macros it defines.
// So we include it and make sure CI warns us if we use something that conflicts
// with a Windows define.
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include "item.h"
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class Inventory : public Node {

	GDCLASS(Inventory, Node);

	TypedArray<Dictionary> slots;
	bool fixed_size;
    
public:
	Inventory();
	~Inventory();
	bool is_fixed_size() const;
	void set_fixed_size(const bool &f_size);
	TypedArray<Dictionary> get_slots() const;
	void set_slots(const TypedArray<Dictionary> &p_slots);
	int add(const Ref<Item> &p_item, const int &p_amount = 1);
	int remove(const Ref<Item> &p_item, const int &p_amount = 1);
	bool contains(const Ref<Item> &p_item, const int &p_amount = 1) const;
	int get_amount_of(const Ref<Item> &p_item, const int &p_amount = 1) const;
	void clear();

protected:
	static void _bind_methods();

private:
	// SLOTS
	int add_to_slot(const int &p_slot_index, const Ref<Item> &p_item, const int &p_amount);
	int remove_from_slot(const int &p_slot_index, const Ref<Item> &p_item, const int &p_amount);

};

#endif // INVENTORY_CLASS_H
