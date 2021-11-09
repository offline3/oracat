#include <iostream>
#include <list>

// 抽象观察者类
class Observer{
    public:
    virtual void update() = 0;
};

// 抽象主题（通知者）类
class Subject{
    public:
    // 添加观察者
    virtual void attach(Observer* o) = 0;
    // 删除观察者
    virtual void detach(Observer* o) = 0;
    // 通知所有观察者
    virtual void notify() = 0;
};

// 具体主题（通知者）类
class ConcreteSubject : public Subject{
    public:
    void attach(Observer* o) override{
        m_observers.push_back(o);
    }
    void detach(Observer* o) override{
        for(auto it = m_observers.begin(); it != m_observers.end(); it++){
            if(*it == o){
                m_observers.erase(it);
                break;
            }
        }
    }
    void notify() override{
        for(auto it = m_observers.begin(); it != m_observers.end(); it++){
            (*it)->update();
        }
    }

    void setSubjectState(std::string state){
        m_subjectState = state;
    }

    std::string getSubjectState(){
        return  m_subjectState;
    }
    private:
    std::string m_subjectState;
    std::list<Observer*> m_observers;
};

// 具体观察者类: 狼人 
class OberverWerewolf : public Observer{
    public:
    OberverWerewolf(std::string name, ConcreteSubject* subject)
    : m_name(name), m_subject(subject)
    {

    }
    void update(){
        std::string msg = m_subject->getSubjectState();
        if(msg == "“狼人请睁眼”"){
            std::cout << "狼人:" << m_name << "收到：" << msg << "消息；睁开了眼睛\n";
        }
        else{
            std::cout << "狼人:" << m_name << "闭眼\n";
        }
        
    }
    private:
    std::string m_name;
    ConcreteSubject* m_subject;
};

// 具体观察者类1 : 
class OberverCivilian : public Observer{
    public:
    OberverCivilian(std::string name, ConcreteSubject* subject)
    : m_name(name), m_subject(subject)
    {

    }

    void update(){
        std::cout << "平民:" << m_name << "收到：" << m_subject->getSubjectState() << "消息；保持闭眼\n";
    }
    private:
    std::string m_name;
    ConcreteSubject* m_subject;
};

int main(){
    ConcreteSubject* subject = new ConcreteSubject;
    OberverCivilian* civilian1 = new OberverCivilian("1号", subject);
    OberverCivilian* civilian2 = new OberverCivilian("2号", subject);
    OberverWerewolf* werewolf1 = new OberverWerewolf("1号", subject);
    OberverWerewolf* werewolf2 = new OberverWerewolf("2号", subject);
    subject->attach(civilian1);
    subject->attach(civilian2);
    subject->attach(werewolf1);
    subject->attach(werewolf2);
    subject->setSubjectState("“狼人请睁眼”");
    subject->notify();
    // 假设2号平民出局，不需要再接收信息
    subject->detach(civilian1);
    subject->setSubjectState("“狼人请闭眼”");
    subject->notify();
}
