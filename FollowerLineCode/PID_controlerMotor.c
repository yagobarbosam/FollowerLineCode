

#define LIMITE 200
#define LIMITE_INT 200

signed int set_point;
signed int erro;
signed int soma_erro;
signed int old_erro;
signed int var_erro;

signed int PID_var;

signed int P;
signed int I;
signed int D;

signed float kp;
signed float ki;
signed float kd;

void setup_setpoint(signed int set) {

    set_point = set;

}

void setup_PID(signed float p, signed float i, signed float d) {

    kp = p;
    ki = i;
    kd = d;

}

void restart_PID(void){
    
    soma_erro = 0;
    
    P = 0;
    I = 0;
    D = 0;
    PID_var = 0;
    
    erro = 0;
    var_erro = 0;
    old_erro = 0;
    
}

signed int PID(signed int entrada) {


    erro = set_point - entrada;

    P = erro*kp;

    soma_erro += erro;

    if (soma_erro > LIMITE_INT) {
        soma_erro = LIMITE_INT;
    }

    if (soma_erro < -LIMITE_INT) {
        soma_erro = -LIMITE_INT;
    }

    I = soma_erro*ki;

    var_erro = erro - old_erro;
    old_erro = erro;

    D = var_erro*kd;

    PID_var = P + I + D;


    if (PID_var > LIMITE) {
        return LIMITE;
    } else if (PID_var < -LIMITE) {
        return -LIMITE;
    } else {
        return PID_var;
    }

}

signed int return_erro(void){

    return erro;

}
