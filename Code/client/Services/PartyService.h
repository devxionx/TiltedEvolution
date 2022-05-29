#pragma once

struct ImguiService;
struct TransportService;
struct UpdateEvent;
struct DisconnectedEvent;
struct NotifyPlayerList;
struct NotifyPartyInfo;
struct NotifyPartyInvite;
struct NotifyPartyJoined;
struct NotifyPartyLeft;

/**
* @brief Manages the party of the local player.
*/
struct PartyService
{
    PartyService(entt::dispatcher& aDispatcher, TransportService& aTransportService) noexcept;
    ~PartyService() = default;

    TP_NOCOPYMOVE(PartyService);

    [[nodiscard]] bool IsInParty() const noexcept
    {
        return m_inParty;
    }
    [[nodiscard]] bool IsLeader() const noexcept
    {
        return m_isLeader;
    }
    [[nodiscard]] uint32_t GetLeaderPlayerId() const noexcept
    {
        return m_leaderPlayerId;
    }

    const Vector<uint32_t>& GetPartyMembers() const noexcept
    {
        return m_partyMembers;
    }
    const Map<uint32_t, String>& GetPlayers() const noexcept
    {
        return m_players;
    }
    Map<uint32_t, uint64_t>& GetInvitations() noexcept
    {
        return m_invitations;
    }

protected:

    void OnUpdate(const UpdateEvent& acEvent) noexcept;
    void OnDisconnected(const DisconnectedEvent& acEvent) noexcept;
    void OnPlayerList(const NotifyPlayerList& acPlayerList) noexcept;
    void OnPartyInfo(const NotifyPartyInfo& acPartyInfo) noexcept;
    void OnPartyInvite(const NotifyPartyInvite& acPartyInvite) noexcept;
    void OnPartyJoined(const NotifyPartyJoined& acPartyJoined) noexcept;
    void OnPartyLeft(const NotifyPartyLeft& acPartyLeft) noexcept;

private:

    void DestroyParty() noexcept;

    Map<uint32_t, String> m_players;
    Map<uint32_t, uint64_t> m_invitations;
    uint64_t m_nextUpdate{0};

    bool m_inParty = false;
    bool m_isLeader = false;
    uint32_t m_leaderPlayerId;
    Vector<uint32_t> m_partyMembers;

    TransportService& m_transportService;

    entt::scoped_connection m_updateConnection;
    entt::scoped_connection m_disconnectConnection;
    entt::scoped_connection m_playerListConnection;
    entt::scoped_connection m_partyInfoConnection;
    entt::scoped_connection m_partyInviteConnection;
    entt::scoped_connection m_partyJoinedConnection;
    entt::scoped_connection m_partyLeftConnection;
};
