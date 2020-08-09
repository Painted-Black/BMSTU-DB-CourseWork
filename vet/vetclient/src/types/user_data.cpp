#include "QJsonHeaders.h"

#include "user_data.h"

bool AccessLevel::deserialize(const QByteArray & value) noexcept
{
	bool is_ok = false;
	if (value == "vet")
	{
		current = AccessLevelEnum::Vet;
		is_ok = true;
	}
	else if (value == "main")
	{
		current = AccessLevelEnum::Main;
		is_ok = true;
	}
	else if (value == "admin")
	{
		current = AccessLevelEnum::Admin;
		is_ok = true;
	}
	else if (value == "registry")
	{
		current = AccessLevelEnum::Registry;
		is_ok = true;
	}

	return is_ok;
}

QByteArray AccessLevel::serialize() const
{
	switch (current)
	{
		case AccessLevelEnum::Vet:
			return "vet";
		case AccessLevelEnum::Main:
			return "main";
		case AccessLevelEnum::Admin:
			return "admin";
		case AccessLevelEnum::Registry:
			return "registry";
	}
}

bool AccessData::deserialize(const QByteArray & data) noexcept
{

}

QByteArray AccessData::serialize() const
{

}
