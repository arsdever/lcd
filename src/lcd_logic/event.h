#pragma once

#include <event_connection.h>
#include <uuid.h>

namespace lcd
{
	template <typename... args>
	class event
	{
	public:
		using connection_t = event_connection<args...>;
		using handler_t	   = std::function<void(args...)>;

	public:
		event() = default;

		connection_t operator+=(handler_t const& handler)
		{
			typename connection_t::uuid_t handler_uuid = uuid::generate_uuid_v4();
			m_handlers.insert({ handler_uuid, handler });
			return connection_t(*this, handler_uuid);
		}

		void operator-=(connection_t const& connection) { m_handlers.erase(connection.handle()); }

		void invoke(args... arguments)
		{
			for (auto handler : m_handlers)
				{
					handler.second(arguments...);
				}
		}

	private:
		std::unordered_map<typename connection_t::uuid_t, handler_t> m_handlers;
	};
} // namespace lcd