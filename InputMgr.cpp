#include "pch.h"
#include "InputMgr.h"

std::map<Axis, AxisInfo> InputMgr::axisInfoMap;
std::list<sf::Keyboard::Key> InputMgr::downList;
std::list<sf::Keyboard::Key> InputMgr::upList;
std::list<sf::Keyboard::Key> InputMgr::ingList;

void InputMgr::Init()
{
    // Horizontal(가로축 입력)
    AxisInfo infoH;
    infoH.axis = Axis::Horizontal;

    infoH.positives.push_back(sf::Keyboard::D);
    infoH.positives.push_back(sf::Keyboard::Right);
    infoH.negatives.push_back(sf::Keyboard::A);
    infoH.negatives.push_back(sf::Keyboard::Left);
    infoH.sensi = 5.f;
    infoH.value = 0.f;

    axisInfoMap.insert({ infoH.axis, infoH });



    // Vertical(세로축 입력)
    AxisInfo infoV;
    infoV.axis = Axis::Vertical;

    // 현재 y축은 아래가 positive임을 주의하자.
    infoV.positives.push_back(sf::Keyboard::S);
    infoV.positives.push_back(sf::Keyboard::Down);
    infoV.negatives.push_back(sf::Keyboard::W);
    infoV.negatives.push_back(sf::Keyboard::Up);
    infoV.sensi = 5.f;
    infoV.value = 0.f;

    axisInfoMap.insert({ infoH.axis, infoH });
}

void InputMgr::UpdateEvent(const sf::Event& ev)
{
    switch (ev.type)
    {
    case sf::Event::KeyPressed:
        if (!GetKey(ev.key.code))
        {
            ingList.push_back(ev.key.code);
            downList.push_back(ev.key.code);
        }
        break;
    case sf::Event::KeyReleased:
        ingList.remove(ev.key.code);
        upList.push_back(ev.key.code);
        break;
    case sf::Event::MouseButtonPressed:
        // 숙제
        break;
    case sf::Event::MouseButtonReleased:
        // 숙제
        break;
    }
}

void InputMgr::Update(float dt)
{
    // 쓰기용으로 쓴다면, 레퍼런스를 사용해야 한다.
    for (auto& pair : axisInfoMap)
    {
        AxisInfo& axisInfo = pair.second;
        float raw = GetAxisRaw(axisInfo.axis); // -1, 0, 1
        float speed = raw;

        if (speed == 0.f && axisInfo.value != 0.f)
        {
            speed = axisInfo.value > 0.f ? -1.f : 1.f;
        }
        axisInfo.value += speed * axisInfo.sensi * dt;
        axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f);
        
        if (raw == 0.f && abs(axisInfo.value) < speed * axisInfo.sensi * dt)
        {
            axisInfo.value = 0.f;
        }
    }
}

void InputMgr::Clear()
{
    downList.clear();
    upList.clear();
}

float InputMgr::GetAxisRaw(Axis axis)
{
    // 등록되지 않은 axis는 0.f로 반환
    auto findInfo = axisInfoMap.find(axis);
    if (findInfo == axisInfoMap.end())
        return 0.f;

    // 나중에 입력받은 키를 탐색: 역방향 순회
    const auto& info = findInfo->second;
    auto it = ingList.rbegin();
    while (it != ingList.rend())
    {
        sf::Keyboard::Key key = *it;

        if (std::find(info.positives.begin(), info.positives.end(), key) != info.positives.end())
        {
            return 1.f;
        }
        if (std::find(info.negatives.begin(), info.negatives.end(), key) != info.negatives.end())
        {
            return -1.f;
        }
        it++;
    }
    return 0.0f;
}

float InputMgr::GetAxis(Axis axis)
{
    auto findInfo = axisInfoMap.find(axis);
    if (findInfo == axisInfoMap.end())
        return 0.f;

    return findInfo->second.value;
}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
    //std::list<sf::Keyboard::Key>::iterator it = downList.begin

    //for (auto it = downList.begin(); it != downList.end(); ++it)
    //{
    //    if (*it == key)
    //        return true;
    //}

    //for (auto k : downList)
    //{
    //    if (k == key)
    //        return true;
    //}

    return std::find(downList.begin(), downList.end(), key) != downList.end();
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
    return std::find(upList.begin(), upList.end(), key) != upList.end();
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
    return std::find(ingList.begin(), ingList.end(), key) != ingList.end();
}

const sf::Vector2f& InputMgr::GetMousePos()
{
    // 숙제
    return (sf::Vector2f)sf::Mouse::getPosition();
}

bool InputMgr::GetMouseButtonDown(sf::Mouse::Button key)
{
    // 숙제
    return false;
}

bool InputMgr::GetMouseButtonUp(sf::Mouse::Button key)
{
    // 숙제
    return false;
}

bool InputMgr::GetMouseButton(sf::Mouse::Button key)
{
    // 숙제
    return false;
}
