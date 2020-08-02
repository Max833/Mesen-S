#include "stdafx.h"
#include "MessageManager.h"

std::unordered_map<string, string> MessageManager::_enResources = {
	{ "Cheats", u8"Cheats" },
	{ "Debug", u8"Debug" },
	{ "EmulationSpeed", u8"Geschwindigkeit" },
	{ "ClockRate", u8"Taktfrequenz" },
	{ "Error", u8"Fehler" },
	{ "GameInfo", u8"Spielinfo" },
	{ "GameLoaded", u8"Spiel geladen" },
	{ "Input", u8"Eingabegeräte" },
	{ "Patch", u8"Patch" },
	{ "Movies", u8"Filme" },
	{ "NetPlay", u8"Netplay" },
	{ "Overclock", u8"Übertaktung" },
	{ "Region", u8"Region" },
	{ "SaveStates", u8"Spielstände" },
	{ "ScreenshotSaved", u8"Screenshot gespeichert" },
	{ "SoundRecorder", u8"Tonaufnahmegerät" },
	{ "Test", u8"Test" },
	{ "VideoRecorder", u8"Videoaufnahmegerät" },

	{ "ApplyingPatch", u8"Patch wird angewendet: %1" },
	{ "CheatApplied", u8"1 Cheat hinzugefügt." },
	{ "CheatsApplied", u8"%1 Cheats wurden hinzugefügt." },
	{ "CheatsDisabled", u8"Alle Cheats deaktiviert." },
	{ "CoinInsertedSlot", u8"Münze eingeworfen (Slot %1)" },
	{ "ConnectedToServer", u8"Verbindung zum Server hergestellt." },
	{ "ConnectedAsPlayer", u8"Als Spieler %1 verbunden" },
	{ "ConnectedAsSpectator", u8"Als Zuschauer verbunden." },
	{ "ConnectionLost", u8"Verbindung zum Server verloren." },
	{ "CouldNotConnect", u8"Es konnte keine Verbindung zum Server hergestellt werden." },
	{ "CouldNotInitializeAudioSystem", u8"Audio-System konnte nicht initialisiert werden" },
	{ "CouldNotFindRom", u8"Es konnte keine übereinstimmende ROM-Datei gefunden werden. (%1)" },
	{ "CouldNotWriteToFile", u8"Die Datei %1 konnte nicht beschrieben werden" },
	{ "CouldNotLoadFile", u8"Die Datei %1 konnte nicht geladen werden" },
	{ "EmulationMaximumSpeed", u8"Maximal-Geschwindigkeit" },
	{ "EmulationSpeedPercent", u8"%1%" },
	{ "FdsDiskInserted", u8"Diskette %1 Seite %2 eingelegt." },
	{ "Frame", u8"Frame" },
	{ "GameCrash", u8"Das Spiel ist abgestürzt (%1)" },
	{ "KeyboardModeDisabled", u8"Tastatur-Modus deaktiviert." },
	{ "KeyboardModeEnabled", u8"Tastatur-Modus aktiviert." },
	{ "Lag", u8"Lag" },
	{ "Mapper", u8"Mapper: %1, Sub-Mapper: %2" },
	{ "MovieEnded", u8"Film gestoppt." },
	{ "MovieInvalid", u8"Film-Datei ungültig." },
	{ "MovieMissingRom", u8"Fehlende ROM-Datei wird benötigt (%1), um den Film abzuspielen." },
	{ "MovieNewerVersion", u8"Filme, die von einer neueren Mesen-S-Version erstellt wurden, können nicht geladen werden. Bitte die aktuellste Version herunterladen." },
	{ "MovieIncompatibleVersion", u8"Film ist mit dieser Mesen-S-Version nicht kompatibel." },
	{ "MoviePlaying", u8"Folgender Film wird abgespielt: %1" },
	{ "MovieRecordingTo", u8"Aufnahme erfolgt unter: %1" },
	{ "MovieSaved", u8"Film-Datei gespeichert unter: %1" },
	{ "NetplayVersionMismatch", u8"%1 verwendet nicht die gleiche Mesen-S-Version und wurde deshalb vom Server getrennt." },
	{ "NetplayNotAllowed", u8"Solange man mit einem Server verbunden ist, ist dies nicht zulässig." },
	{ "OverclockEnabled", u8"Übertaktung aktiviert." },
	{ "OverclockDisabled", u8"Übertaktung deaktiviert." },
	{ "PrgSizeWarning", u8"PRG-Größe ist kleiner als 32kb" },
	{ "SaveStateEmpty", u8"Slot ist leer." },
	{ "SaveStateIncompatibleVersion", u8"Spielstand ist mit dieser Mesen-S-Version nicht kompatibel." },
	{ "SaveStateInvalidFile", u8"Spielstand-Datei ungültig." },
	{ "SaveStateWrongSystemSnes", u8"Fehler: Spielstand kann nicht geladen werden (falscher Konsolen-Typ: SNES)" },
	{ "SaveStateWrongSystemGb", u8"Fehler: Spielstand kann nicht geladen werden (falscher Konsolen-Typ: Game Boy)" },
	{ "SaveStateLoaded", u8"Spielstand #%1 geladen." },
	{ "SaveStateMissingRom", u8"Fehlende ROM-Datei wird benötigt (%1), um den Spielstand zu laden." },
	{ "SaveStateNewerVersion", u8"Spielstände, die von einer neueren Mesen-S-Version erstellt wurden, können nicht geladen werden. Bitte die aktuellste Version herunterladen." },
	{ "SaveStateSaved", u8"Spielstand #%1 gespeichert." },
	{ "SaveStateSlotSelected", u8"Slot #%1 ausgewählt." },
	{ "ScanlineTimingWarning", u8"PPU-Timing wurde geändert." },
	{ "ServerStarted", u8"Server gestartet (Port: %1)" },
	{ "ServerStopped", u8"Server gestoppt" },
	{ "SoundRecorderStarted", u8"Aufnahme erfolgt unter: %1" },
	{ "SoundRecorderStopped", u8"Aufnahme gespeichert unter: %1" },
	{ "TestFileSavedTo", u8"Test-Datei gespeichert unter: %1" },
	{ "UnsupportedMapper", u8"Mapper nicht unterstützt (%1), Spiel kann nicht geladen werden." },
	{ "VideoRecorderStarted", u8"Aufnahme erfolgt unter: %1" },
	{ "VideoRecorderStopped", u8"Aufnahme gespeichert unter: %1" },
};

std::list<string> MessageManager::_log;
SimpleLock MessageManager::_logLock;
SimpleLock MessageManager::_messageLock;
bool MessageManager::_osdEnabled = true;
IMessageManager* MessageManager::_messageManager = nullptr;

void MessageManager::RegisterMessageManager(IMessageManager* messageManager)
{
	auto lock = _messageLock.AcquireSafe();
	MessageManager::_messageManager = messageManager;
}

void MessageManager::UnregisterMessageManager(IMessageManager* messageManager)
{
	auto lock = _messageLock.AcquireSafe();
	if(MessageManager::_messageManager == messageManager) {
		MessageManager::_messageManager = nullptr;
	}
}

void MessageManager::SetOsdState(bool enabled)
{
	_osdEnabled = enabled;
}

string MessageManager::Localize(string key)
{
	std::unordered_map<string, string> *resources = &_enResources;
	/*switch(EmulationSettings::GetDisplayLanguage()) {
		case Language::English: resources = &_enResources; break;
		case Language::French: resources = &_frResources; break;
		case Language::Japanese: resources = &_jaResources; break;
		case Language::Russian: resources = &_ruResources; break;
		case Language::Spanish: resources = &_esResources; break;
		case Language::Ukrainian: resources = &_ukResources; break;
		case Language::Portuguese: resources = &_ptResources; break;
		case Language::Catalan: resources = &_caResources; break;
		case Language::Chinese: resources = &_zhResources; break;
	}*/
	if(resources) {
		if(resources->find(key) != resources->end()) {
			return (*resources)[key];
		}/* else if(EmulationSettings::GetDisplayLanguage() != Language::English) {
			//Fallback on English if resource key is missing another language
			resources = &_enResources;
			if(resources->find(key) != resources->end()) {
				return (*resources)[key];
			}
		}*/
	}

	return key;
}

void MessageManager::DisplayMessage(string title, string message, string param1, string param2)
{
	if(MessageManager::_messageManager) {
		auto lock = _messageLock.AcquireSafe();
		if(!MessageManager::_messageManager) {
			return;
		}

		title = Localize(title);
		message = Localize(message);

		size_t startPos = message.find(u8"%1");
		if(startPos != std::string::npos) {
			message.replace(startPos, 2, param1);
		}

		startPos = message.find(u8"%2");
		if(startPos != std::string::npos) {
			message.replace(startPos, 2, param2);
		}

		if(_osdEnabled) {
			MessageManager::_messageManager->DisplayMessage(title, message);
		} else {
			MessageManager::Log("[" + title + "] " + message);
		}
	}
}

void MessageManager::Log(string message)
{
#ifndef LIBRETRO
	auto lock = _logLock.AcquireSafe();
	if(message.empty()) {
		message = "------------------------------------------------------";
	}
	if(_log.size() >= 1000) {
		_log.pop_front();
	}
	_log.push_back(message);
#else
	if(MessageManager::_messageManager) {
		MessageManager::_messageManager->DisplayMessage("", message + "\n");
	}
#endif
}

void MessageManager::ClearLog()
{
	auto lock = _logLock.AcquireSafe();
	_log.clear();
}

string MessageManager::GetLog()
{
	auto lock = _logLock.AcquireSafe();
	stringstream ss;
	for(string &msg : _log) {
		ss << msg << "\n";
	}
	return ss.str();
}
