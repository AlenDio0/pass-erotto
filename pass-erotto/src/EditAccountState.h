#pragma once
#include "AddAccountState.h"

#include "Data.h"

#include <unordered_map>
#include "TextButton.h"
#include "TextBox.h"
#include "AccountInfo.h"
#include "Notify.h"

class EditAccountState : public AddAccountState
{
public:
	EditAccountState(const AccountInfo& account);

	void init() override;
private:
	AccountInfo m_OriginalAccountInfo;

	void onConfirmButton() override;
};