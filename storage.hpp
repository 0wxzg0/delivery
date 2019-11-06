/*

*/

#include<time.h>

class package{
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

        bool isCancled();
        void judgeInfo(ItemMessage msg);
        void setPackage(int id,const char* address,int size,int weight,int type);
        void showInformation();
        void setStatus(int s);
        void showStatus();
        void setDeliver(int name);
        void setTime(int t);
        void showTime(int t);
        tm estimateTime(tm t);
        void printReceipt(double money);
        bool operator<(const package &p){
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

char package::statusMap[6]={"123456"};
char package::sizeMap[5]={"12345"};
char package::weightMap[5]={"12345"};

bool package::isCancled(){
    return (!status)true:false;
}

/*
Task:
1:新包裹
2:修改包裹状态
3:显示包裹信息
4:打印收据
*/

void package::judgeInfo(ItemMessage msg){
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

void package::setPackage(int id,const char* address,int size,int weight,int type){
	for(int i=0;i<10;i++)
        *(orderNumber+i)=rand()%10+'0'; //随机生成编号
    idOfCustomer=id;
    strcpy(addressDeliverTo,address);
	sizeOfPackage=size;
    weightOfPackage=weight;
    typeOfService=type;
    priceOfPackage=size*weight*type; //计算价格的方法
    setStatus(1);
    setDeliver(findDeliver(*address)); //根据包裹信息设置快递员（未定义）
}

void package::showInformation(){
	showCustomerInfo(*id); //用户信息(未定义)
    cout<<"Deliver To:"<<addressDeliverTo<<endl;
    cout<<"Price:"<<priceOfPackage<<endl;
    cout<<"Service:"<<serviceMap[typeOfService]<<endl;
    showStatus();
}

void package::setStatus(int s){
    status=s;
    setTime(status);
}

void package::showStatus(){
	cout<<statusMap[status]; //显示包裹状态
}

void package::setDeliver(int name){
    deliver=name;
}
void package::printReceipt(double money){ //money:收到的
    cout<<priceOfPackage; //收据信息
}

tm package::estimateTime(tm t){
    tm tt=t;
    if(typeOfService==2)
        tt.hour+=2;
    if(typeOfService==3)
        tt.mday+=1;
    return tt;
}

void package::setTime(int t){
    *timeInfo[t]=localtime(&now); //设置时间
}

void package::showTime(int t){
    tm T;
    if(t!=1) T=timeInfo[t];
    else T=estimateTime(t);
    cout<<T.tm_year<<"/"<<T.tm_mon<<"/"<<T.tm_mday<<" ";
    cout<<T.tm_hour<<":"<<T.tm_min<<":"<<T.tm_sec<<endl;
}