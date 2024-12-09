class_name DoubleValueEffect
extends Effect

export(int) var value2 = 0


static func get_id() -> String:
	return "double_value"


func apply(player_index: int) -> void:
	var effects = RunData.get_player_effects(player_index)

	if custom_key != "" or storage_method == StorageMethod.KEY_VALUE:
		effects[custom_key].push_back([key, value, value2])
	else:
		effects[key].push_back([value, value2])


func unapply(player_index: int) -> void:
	var effects = RunData.get_player_effects(player_index)

	if custom_key != "" or storage_method == StorageMethod.KEY_VALUE:
		effects[custom_key].erase([key, value, value2])
	else:
		effects[key].erase([value, value2])


func get_args(_player_index: int) -> Array:
	return [str(value), tr(key.to_upper()), str(value2)]


func serialize() -> Dictionary:
	var serialized = .serialize()

	serialized.value2 = value2

	return serialized


func deserialize_and_merge(serialized: Dictionary) -> void:
	.deserialize_and_merge(serialized)

	value2 = serialized.value2
