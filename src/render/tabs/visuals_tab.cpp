#include "../render.h"
#include "../../globals.h"
#include "../../settings.h"
#include "../../helpers/imdraw.h"
#include "../../helpers/console.h"
#include "../..//features/features.h"

extern void bind_button(const char* eng, const char* rus, int& key);
extern bool hotkey(const char* label, int* k, const ImVec2& size_arg = ImVec2(0.f, 0.f));

namespace render
{
	namespace menu
	{
		void visuals_tab()
		{
			child("ESP", []()
			{
				columns(2);
				{
					checkbox("Enabled", u8"��������", &settings::esp::enabled);

					ImGui::NextColumn();

					ImGui::PushItemWidth(-1);
					hotkey("##binds.esp", &globals::binds::esp);
					ImGui::PopItemWidth();
				}
				columns(1);

				checkbox("Visible Only", u8"�������� ���������", &settings::esp::visible_only);

				checkbox("Name", u8"���", &settings::esp::names);
				checkbox("Weapon", u8"������", &settings::esp::weapons);
				checkbox("Player Info Box", &settings::visuals::player_info_box);
				checkbox("Grief Box", &settings::visuals::grief_box);

				columns(2);
				{
					checkbox("Boxes", u8"�����", &settings::esp::boxes);

					ImGui::NextColumn();

					const char* box_types[] = {
						___("Normal", u8"�������"), ___("Corner", u8"�������")
					};

					ImGui::PushItemWidth(-1);
					{
						ImGui::Combo("##esp.box_type", &settings::esp::box_type, box_types, IM_ARRAYSIZE(box_types));
					}
					ImGui::PopItemWidth();
				}
				ImGui::Columns(1);

				const char* positions[] =
				{
					___("Left", u8"�����"),
					___("Right", u8"������"),
					___("Bottom", u8"�����"),
				};

				const char* HealthPositions[] =
				{
					___("Left", u8"�����"),
					___("Right", u8"������"),
					___("Bottom", u8"�����"),
					___("Number", u8"�����"),
				};

				columns(2);
				{
					checkbox("Health", u8"��������", &settings::esp::health);

					ImGui::NextColumn();

					ImGui::PushItemWidth(-1);
					ImGui::Combo("##health.position", &settings::esp::health_position, HealthPositions, IM_ARRAYSIZE(HealthPositions));
					ImGui::PopItemWidth();
				}
				columns(1);

				columns(2);
				{
					checkbox("Armor", u8"�����", &settings::esp::armour);

					ImGui::NextColumn();

					ImGui::PushItemWidth(-1);
					ImGui::Combo("##armor.position", &settings::esp::armour_position, positions, IM_ARRAYSIZE(positions));
					ImGui::PopItemWidth();
				}
				columns(1);

				//checkbox("Dormant", &Settings::ESP::dormant);
				checkbox("Is Scoped", &settings::esp::is_scoped);
				checkbox("Is Flashed", &settings::esp::is_flashed);
				checkbox("Is Defusing", &settings::esp::is_defusing);
				checkbox("Snap Lines", &settings::esp::snaplines);
				checkbox("Ammo ESP", &settings::esp::ammo);
				checkbox("Money ESP", &settings::esp::money);
				checkbox("Choke ESP", &settings::visuals::choke);
				checkbox("Sound ESP", &settings::esp::soundesp);
				//checkbox("Beams", u8"���� �����", &settings::esp::beams); //Doesnt work.
				//checkbox("Sound Direction (?)", &settings::esp::sound); //Doesnt work.
				//tooltip("Sound ESP", u8"���������� ��������� ����������� �����, ������ ������ ������.");

				checkbox("Bomb Damage ESP", &settings::esp::bomb_esp);
				checkbox("Has Kit ESP", &settings::esp::haskit);

				checkbox("Offscreen ESP", u8"����� ����������� (?)", &settings::esp::offscreen);
				checkbox("Enemy Armor Status (?)", &settings::esp::kevlarinfo);
				tooltip("Will display HK if enemy has kevlar + helmer or K if enemy has kevlar only.");
			});

			ImGui::NextColumn();

			child(___("Chams", u8"������� ������"), []()
			{
				/* //Old chams
					checkbox("Enabled", u8"��������", &settings::chams::enabled);
					checkbox("Visible Only", u8"�������� ���������", &settings::chams::visible_only);
					checkbox("Wireframe", u8"�����", &settings::chams::wireframe);
					checkbox("Flat", &settings::chams::flat);
				*/

				static const char* ChamsTypes[] = {
				"Visible - Normal",
				"Visible - Flat",
				"Visible - Wireframe",
				"Visible - Glass",
				"Visible - Metallic",
				"XQZ",
				"Metallic XQZ",
				"Flat XQZ"
				};

				static const char* bttype[] = {
				"Off",
				"Last Tick",
				"All Ticks"
				};

				columns(2);
				{
					checkbox("Enemy", &settings::chams::enemynew);

					ImGui::NextColumn();

					ImGui::PushItemWidth(-1);
					ImGui::Combo("Enemy - Mode", &settings::chams::enemymodenew, ChamsTypes, IM_ARRAYSIZE(ChamsTypes));
					ImGui::PopItemWidth();
				}
				columns(1);

				columns(2);
				{
					checkbox("Team", &settings::chams::teamnew);

					ImGui::NextColumn();

					ImGui::PushItemWidth(-1);
					ImGui::Combo("Team - Mode", &settings::chams::teammodenew, ChamsTypes, IM_ARRAYSIZE(ChamsTypes));
					ImGui::PopItemWidth();
				}
				columns(1);

				columns(2);
				{
					checkbox("Local", &settings::chams::localnew);

					ImGui::NextColumn();

					ImGui::PushItemWidth(-1);
					ImGui::Combo("Local - Mode", &settings::chams::localmodenew, ChamsTypes, IM_ARRAYSIZE(ChamsTypes));
					ImGui::PopItemWidth();
				}
				columns(1);

				checkbox("Real Angle   ", &settings::chams::desync);		//checkbox("Viewmodel Weapons", &settings::chams::wepchams);
				ImGui::SameLine();
				checkbox("Planted C4", &settings::chams::plantedc4_chams);
				checkbox("Weapons (?)", &settings::chams::wep_droppedchams);
				tooltip("Dropped Weapons Chams");
				ImGui::SameLine();
				checkbox("Nades", &settings::chams::nade_chams);

				//separator("BT Chams - Mode");
				//ImGui::Combo("BT Chams Mode", &settings::chams::bttype, bttype, IM_ARRAYSIZE(bttype));
				//checkbox("BT Chams - Flat", &settings::chams::btflat);
				//ColorEdit4("BT Color", &settings::chams::btcolor);

				/*separator("Arms", u8"����");

				checkbox("Enabled##arms", u8"��������##arms", &settings::chams::arms::enabled);
				checkbox("Wireframe##arms", u8"�����##arms", &settings::chams::arms::wireframe);

				ImGui::Separator();

				ColorEdit4(___("Visible", u8"�������"), &settings::chams::visible_color);
				ColorEdit4(___("Occluded", u8"�� ���������"), &settings::chams::occluded_color);

				ColorEdit4(___("Arms", u8"����"), &settings::chams::arms::color); */

				child(___("Glow", u8"������� ������"), []()
				{
					checkbox("Enemy", &settings::glow::GlowEnemyEnabled);
					ImGui::SameLine();
					checkbox("Planted C4", &settings::glow::GlowC4PlantedEnabled);
					ImGui::SameLine();
					checkbox("Nades", &settings::glow::GlowNadesEnabled);
					checkbox("Team  ", &settings::glow::GlowTeamEnabled);
					ImGui::SameLine();
					checkbox("Weapons (?)", &settings::glow::GlowDroppedWeaponsEnabled);
					tooltip("Dropped Weapons Glow");
				});

			});

			ImGui::NextColumn();

			child(___("Extra", u8"������"), []()
			{
				static const char* cross_types[] = {
					"Type: Crosshair",
					"Type: Circle"
				};

				static const char* hitmarkersounds[] = {
					"Sound: Cod",
					"Sound: Skeet",
					"Sound: Punch",
					"Sound: Metal",
					"Sound: Boom"
				};

				checkbox("Planted C4", &settings::visuals::planted_c4);
				checkbox("Defuse Kits", u8"������", &settings::visuals::defuse_kit);
				checkbox("World Weapons", u8"��������� ������", &settings::visuals::dropped_weapons);
				checkbox("World Grenades", u8"��������� ������", &settings::visuals::world_grenades);
				checkbox("Sniper Crosshair", u8"����������� ������", &settings::visuals::sniper_crosshair);
				checkbox("Grenade Prediction", u8"������� ������ ������", &settings::visuals::grenade_prediction);
				checkbox("Aimbot Fov", &settings::esp::drawFov);
				checkbox("Spread Crosshair", &settings::visuals::spread_cross);
				checkbox("Bullet Tracer", &settings::visuals::bullet_tracer);
				checkbox("Hitmarker", &settings::visuals::hitmarker);
				ImGui::Combo("Hitmarker Sound", &settings::visuals::hitsound, hitmarkersounds, IM_ARRAYSIZE(hitmarkersounds));
				checkbox("RCS Crosshair", &settings::visuals::rcs_cross);
				ImGui::Combo("RCS Crosshair Type", &settings::visuals::rcs_cross_mode, cross_types, IM_ARRAYSIZE(cross_types));
				if (settings::visuals::rcs_cross_mode == 1)
					ImGui::SliderFloatLeftAligned("Radius", &settings::visuals::radius, 8.f, 18.f, "%.1f");

				const auto old_night_state = settings::visuals::night_mode;
				const auto old_style_state = settings::visuals::newstyle;
				checkbox("Night Mode", u8"������ �����", &settings::visuals::night_mode);

				if (settings::visuals::night_mode)
				{
					ImGui::SliderFloatLeftAligned(___("Night Mode Intensity:", u8"������:"), &settings::esp::mfts, 0.0f, 1.0f, "%.1f %");

					if (ImGui::Button("Apply", ImVec2(ImGui::GetContentRegionAvailWidth(), 0.f)))
					{
						color_modulation::SetMatForce();
					}
				}

				checkbox("Chance ESP (?)", &settings::misc::esp_random);
				tooltip("Enables/disables the esp/chams based on chance, that is generated per round.Set chance manually.");

				if (settings::misc::esp_random)
				{
					ImGui::SliderIntLeftAligned("ESP Chance (?)", &settings::esp::esp_chance, 1, 100, "%.0f %%");
					tooltip("Will turn esp/chams on/off if chance is higher/smaller or equal than set value");
				}

				checkbox("Dark Menu", &settings::visuals::newstyle);
				if (old_style_state != settings::visuals::newstyle) //settings::visuals::night_mode
					imdraw::apply_style(settings::visuals::newstyle);
			});
		}
	}
}