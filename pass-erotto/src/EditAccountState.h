#pragma once
#include "AddAccountState.h"

#include "AccountInfo.h"

class EditAccountState : public AddAccountState
{
public:
	EditAccountState(const AccountInfo& account);

	void init() override;
private:
	AccountInfo m_OriginalAccountInfo;

	void onConfirmButton() override;
};