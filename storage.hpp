/*

*/

#include<time.h>

class Package{
	private:
        char* orderNumber;
        int idOfCustomer;
        char* addressDeliverTo;
        int sizeOfPackage;
        int weightOfPackage;
        int typeOfService;
        double priceOfPackage;
        int status;
        int deliver;
        tm timeInfo[6];
    public:
        static char statusMap[6];
        static char sizeMap[5];
        static char weightMap[5];

        Package();
        Package(int id,const char* address,int size,int weight,int type);

        bool isCancled();
        void judgeInfo(ItemMessage msg);
        void showInformation();
        void setStatus(int s);
        char getStatus();
        void setDeliver(int name);
        void setTime(int t);
        tm getTime(int t);
        tm estimateTime(tm t);
        void printReceipt(double money);
        bool operator<(const Package &p){
            if(this->typeOfService!=p.typeOfService)
                return this->typeOfService<p.typeOfService;
            else{ //假设订单在同一个月
                if(this->timeInfo[0].tm_mday!=p.timeInfo[0].tm_mday)
                    return this->timeInfo[0].tm_mday<p.timeInfo[0].tm_mday;
                else if(this->timeInfo[0].tm_hour!=p.timeInfo[0].tm_hour)
                    return this->timeInfo[0].tm_hour<p.timeInfo[0].tm_hour;
                else if(this->timeInfo[0].tm_min!=p.timeInfo[0].tm_min)
                    return this->timeInfo[0].tm_min<p.timeInfo[0].tm_min;
                else return this->timeInfo[0].tm_sec!=p.timeInfo[0].tm_sec;

            }
        }
};

//typeOfService:1:三小时 2:当天 3:次日送达

//statusMap:"cancelled","ready for pickup","picked up","arrived at warehouse","out of delivery","delivered"

char Package::statusMap[6]={"123456"};
char Package::sizeMap[5]={"12345"};
char Package::weightMap[5]={"12345"};

bool Package::isCancled(){
    return (!status)true:false;
}

/*
Task:
1:新包裹
2:修改包裹状态
3:显示包裹信息
4:打印收据
*/

void Package::judgeInfo(ItemMessage msg){
    char* t=msg.Task;
    char*m=msg.Msg; //未处理
    switch(*t):
    case '1':

        setPackage();
        break;
    case '2':

        setStatus();
        break;
    case '3':

        showInformation();
        break;
    case '4':

        printReceipt();
        break;
}

Package::Package(){
    for(int i=0;i<5;i++)
        *(orderNumber+i)='0';
    idOfCustomer=0;
    strcpy(addressDeliverTo,address);
	sizeOfPackage=0;
    weightOfPackage=0;
    typeOfService=0;
    priceOfPackage=0;
    setStatus(0);
    deliver=0;
}

Package::Package(int id,const char* address,int size,int weight,int type){
	for(int i=0;i<5;i++)
        *(orderNumber+i)=rand()%10+'0'; //随机生成编号
    idOfCustomer=id;
    strcpy(addressDeliverTo,address);
	sizeOfPackage=size;
    weightOfPackage=weight;
    typeOfService=type;
    priceOfPackage=size*weight*type; //计算价格的方法
    setStatus(1);
    deliver=findDeliver(*address); //根据包裹信息设置快递员（未定义）
}

void Package::showInformation(){
	showCustomerInfo(*id); //用户信息(未定义)
    cout<<"Deliver To:"<<addressDeliverTo<<endl;
    cout<<"Price:"<<priceOfPackage<<endl;
    cout<<"Service:"<<serviceMap[typeOfService]<<endl;
    showStatus();
}

void Package::setStatus(int s){
    status=s;
    setTime(status);
}

char Package::getStatus(){
	return statusMap[status]; //显示包裹状态
}

void Package::printReceipt(double money){ //money:收到的
    cout<<priceOfPackage; //收据信息
}

tm Package::estimateTime(tm t){
    tm tt=t;
    if(typeOfService==2)
        tt.hour+=2;
    if(typeOfService==3)
        tt.mday+=1;
    return tt;
}

void Package::setTime(int t){
    *timeInfo[t]=localtime(&now); //设置时间
}

tm Package::getTime(int t){
    if(t!=1) return timeInfo[t];
    else return estimateTime(t);
    
}