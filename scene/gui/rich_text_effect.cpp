#include "rich_text_effect.h"

#include "core/script_language.h"

void RichTextEffect::_bind_methods() {
	BIND_VMETHOD(MethodInfo(Variant::INT, "_process_custom_fx", PropertyInfo(Variant::OBJECT, "char_fx", PROPERTY_HINT_RESOURCE_TYPE, "CustomFXChar")));
}

Variant RichTextEffect::get_bbcode() const {
	Variant r;
	if (get_script_instance()) {
		if (!get_script_instance()->get("bbcode", r)) {
			String path = get_script_instance()->get_script()->get_path();
			r = path.get_file().get_basename();
		}
	}
	return r;
}

bool RichTextEffect::_process_effect_impl(Ref<CharFXTransform> cfx) {
	Variant v = false;
	if (get_script_instance()) {
		v = get_script_instance()->call("_process_custom_fx", cfx);
		if (v.get_type() != Variant::BOOL) {
			v = false;
		}
	}
	return v;
}

RichTextEffect::RichTextEffect() {
}

void CharFXTransform::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_relative_index"), &CharFXTransform::get_relative_index);
	ClassDB::bind_method(D_METHOD("set_relative_index", "i"), &CharFXTransform::set_relative_index);

	ClassDB::bind_method(D_METHOD("get_absolute_index"), &CharFXTransform::get_absolute_index);
	ClassDB::bind_method(D_METHOD("set_absolute_index", "i"), &CharFXTransform::set_absolute_index);

	ClassDB::bind_method(D_METHOD("get_elapsed_time"), &CharFXTransform::get_elapsed_time);
	ClassDB::bind_method(D_METHOD("set_elapsed_time", "t"), &CharFXTransform::set_elapsed_time);

	ClassDB::bind_method(D_METHOD("is_visible"), &CharFXTransform::is_visible);
	ClassDB::bind_method(D_METHOD("set_visibility", "vis"), &CharFXTransform::set_visibility);

	ClassDB::bind_method(D_METHOD("get_offset"), &CharFXTransform::get_offset);
	ClassDB::bind_method(D_METHOD("set_offset", "off"), &CharFXTransform::set_offset);

	ClassDB::bind_method(D_METHOD("get_color"), &CharFXTransform::get_color);
	ClassDB::bind_method(D_METHOD("set_color", "c"), &CharFXTransform::set_color);

	ClassDB::bind_method(D_METHOD("get_environment"), &CharFXTransform::get_environment);
	ClassDB::bind_method(D_METHOD("set_environment", "d"), &CharFXTransform::set_environment);

	ClassDB::bind_method(D_METHOD("get_character"), &CharFXTransform::get_character);
	ClassDB::bind_method(D_METHOD("set_character"), &CharFXTransform::set_character);

	ClassDB::bind_method(D_METHOD("get_or", "key", "default_value"), &CharFXTransform::get_or);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "relative_index"), "set_relative_index", "get_relative_index");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "absolute_index"), "set_absolute_index", "get_absolute_index");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "elapsed_time"), "set_elapsed_time", "get_elapsed_time");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "visible"), "set_visibility", "is_visible");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "offset"), "set_offset", "get_offset");
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "env"), "set_environment", "get_environment");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "character"), "set_character", "get_character");
}

Variant CharFXTransform::get_or(String key, Variant default_value) {
	if (!this->environment.has(key))
		return default_value;

	Variant r = environment[key];
	if (r.get_type() != default_value.get_type())
		return default_value;

	return r;
}

CharFXTransform::CharFXTransform() {
	relative_index = 0;
	absolute_index = 0;
	visibility = true;
	offset = Point2();
	color = Color();
	character = 0;
}
