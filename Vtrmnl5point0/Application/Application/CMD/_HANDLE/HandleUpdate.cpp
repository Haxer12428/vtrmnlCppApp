#include "../Cmd.h"

const void Cmd::HANDLE_UPDATE() {
	std::thread REALTIME_UPDATE([&] {
		do {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

			if (
				this->FORCE_UPDATE
				) {
				this->Update(); this->Refresh(); this->FORCE_UPDATE = false;
			}
		} while (
			true
			);
		}
	);
	REALTIME_UPDATE.detach();
}