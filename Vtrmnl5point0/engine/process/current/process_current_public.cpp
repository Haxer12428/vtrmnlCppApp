#include "../../engine.h"

const bool engine::process::current::is_administrator() {
	BOOL elevated = FALSE;
	HANDLE token_handle = NULL;
	TOKEN_ELEVATION elevation;
	DWORD dw_size;

	if (
		!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token_handle)
		) {
		CloseHandle(token_handle); return false;
	}

	if (
		!GetTokenInformation(token_handle, TokenElevation, &elevation, sizeof elevation, &dw_size)
		) {
		CloseHandle(token_handle); return false;
	}

	elevated = elevation.TokenIsElevated;
	CloseHandle(token_handle);

	return elevated;
}