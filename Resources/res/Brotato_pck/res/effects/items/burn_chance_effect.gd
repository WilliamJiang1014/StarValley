class_name BurnChanceEffect
extends Effect

export(Resource) var burning_data = null


static func get_id() -> String:
	return "burn_chance"


func apply(player_index: int) -> void:
	var effects = RunData.get_player_effects(player_index)
	effects["burn_chance"].merge(burning_data)


func unapply(player_index: int) -> void:
	var effects = RunData.get_player_effects(player_index)
	effects["burn_chance"].remove(burning_data)


func get_args(player_index: int) -> Array:
	var current_burning_data = WeaponService.init_burning_data(burning_data, player_index, true)
	var stat_elemental_damage = Utils.get_scaling_stat_icon_text("stat_elemental_damage")
	return [str(current_burning_data.chance * 100.0), str(current_burning_data.duration), str(current_burning_data.damage), stat_elemental_damage]


func serialize() -> Dictionary:
	var serialized = .serialize()

	if burning_data != null:
		serialized.burning_data = burning_data.serialize()

	return serialized


func deserialize_and_merge(serialized: Dictionary) -> void:
	.deserialize_and_merge(serialized)

	if serialized.has("burning_data"):
		var data = BurningData.new()
		data.deserialize_and_merge(serialized.burning_data)
		burning_data = data


func _add_custom_args() -> void:
	var duration_as_neutral := CustomArg.new()
	duration_as_neutral.arg_index = 1
	duration_as_neutral.arg_sign = Sign.NEUTRAL
	custom_args.append(duration_as_neutral)
