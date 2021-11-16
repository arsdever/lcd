#pragma once

namespace lcd
{
	template <typename... args>
	class event;

	template <typename... args>
	class event_connection
	{
	public:
		using uuid_t  = std::string;
		using event_t = event<args...>;

	public:
		event_connection(event_t& e, uuid_t const& uuid) : m_event(e), m_uuid(uuid) { }

		void disconnect() { m_event -= *this; }

		uuid_t handle() const { return m_uuid; }

	private:
		event_t&	m_event;
		uuid_t m_uuid;
	};
} // namespace lcd