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

using namespace godot;

class Inventory : public Node {

	GDCLASS(Inventory, Node);

	bool fixed_size;
    
public:
	Inventory();
	~Inventory();
	bool is_fixed_size() const;
	void set_fixed_size(const bool &f_size);

protected:
	static void _bind_methods();

};

#endif // INVENTORY_CLASS_H
