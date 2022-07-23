void maze_scan(bool mode) {
  while (1) { //infinite loop
    reading();
    if (sum == 0) {
      if (flag != 's') {
        brake();
        (flag == 'l') ? motor(-6 * spl, 6 * spr) : motor(6 * spl, -6 * spr);
        while (s[2] == 0 && s[3] == 0) reading();
        (flag == 'r') ? motor(-6 * spl, 6 * spr) : motor(6 * spl, -6 * spr); delay(turn_brake);
        flag = 's'; cross = 's'; pos = 0; //when you are done turning robot, make the flag to its normal state so that robot wont turn on its own when it finds no line without detecting 90degree logic
      }
      else if (pos > -3 && pos < 3) {
        m2 = millis();
        while (sum == 0) {
          reading();
          if (millis() - m2 > u_turn_delay) {
            brake(); digitalWrite(light, HIGH);
            (side == 'l') ? motor(-6 * spl, 6 * spr) : motor(6 * spl, -6 * spr);
            while (s[2] == 0 && s[3] == 0) reading();
            (side == 'r') ? motor(-6 * spl, 6 * spr) : motor(6 * spl, -6 * spr); delay(turn_brake);
            path[counter] = 4;
            counter++; digitalWrite(light, LOW);
            pos = 0; break;
          }
        }
      }
    }
    else if (sum == 1 || sum == 2) {  //only for straight line
      if (cross != 's') {
        brake();
        (cross == 'l') ? motor(-6 * spl, 6 * spr) : motor(6 * spl, -6 * spr);
        while (s[4] + s[3] + s[2] + s[1] > 0) reading();
        while (s[2] == 0 && s[3] == 0) reading();
        (flag == 'r') ? motor(-6 * spl, 6 * spr) : motor(6 * spl, -6 * spr); delay(turn_brake);
        cross = 's'; flag = 's'; pos = 0;
      }
      if (sensor == 0b001100) {
        if (pos != 0) {
          (pos > 0) ? motor(-10 * spl, 10 * spr) : motor(10 * spl, -10 * spr);
          (pos > 0) ? delay(pos * 5) : delay(-pos * 5); pos = 0; //this logic is for those whose bot is wabbling during high speed run. this logic will forcefully return bot to its midpoint. don't give more than 30ms delay here!
        }
        motor(10 * spl, 10 * spr);
      }
      //right side portion
      else if (sensor == 0b000100) motor(10 * spl, 9 * spr);
      else if (sensor == 0b000110) {
        if (pos < 1) pos = 1; motor(10 * spl, 6 * spr);
      }
      else if (sensor == 0b000010) {
        if (pos < 2) pos = 2; motor(10 * spl, 3 * spr);
      }
      else if (sensor == 0b000011) {
        if (pos < 3) pos = 3; motor(10 * spl, 0 * spr);
      }
      else if (sensor == 0b000001) {
        if (pos < 4) pos = 4; motor(10 * spl, -3 * spr);
      }
      //left side portion
      else if (sensor == 0b001000) motor(9 * spl, 10 * spr);
      else if (sensor == 0b011000) {
        if (pos > -1) pos = -1; motor(6 * spl, 10 * spr);
      }
      else if (sensor == 0b010000) {
        if (pos > -2) pos = -2; motor(3 * spl, 10 * spr);
      }
      else if (sensor == 0b110000) {
        if (pos > -3) pos = -3; motor(0 * spl, 10 * spr);
      }
      else if (sensor == 0b100000) {
        if (pos > -4) pos = -4; motor(-3 * spl, 10 * spr);
      }
    }

    else if (sum == 3 || sum == 4 || sum == 5) {
      if (s[5] == 1 && s[0] == 0 && s[2] + s[3] > 0) {
        flag = 'l';
        while (s[5] == 1 && s[0] == 0) reading();
        if (s[0] == 0) {
          delay(node_delay);
          reading();
          if (sum != 0) {
            if (side == 'l') cross = 'l';
            (side == 'l') ? path[counter] = 1 : path[counter] = 2;
            counter++; digitalWrite(light, HIGH);
          }
        }
      }

      else if (s[0] == 1 && s[5] == 0 && s[2] + s[3] > 0) {
        flag = 'r';
        while (s[5] == 0 && s[0] == 1) reading();
        if (s[5] == 0) {
          delay(node_delay);
          reading();
          if (sum != 0) {
            if (side == 'r') cross = 'r';
            (side == 'r') ? path[counter] = 3 : path[counter] = 2;
            counter++; digitalWrite(light, HIGH);
          }
        }
      }
      m1 = millis();
    }

    else if (sum == 6) {
      flag = side;
      m2 = millis();
      while (s[5] == 1 || s[0] == 1) {
        reading();
        if (millis() - m2 > stop_timer) {
          brake(); path[counter] = 5; counter++;
          algorithm(); recording();
          if (mode) {
            rotate_backwards(); // rotate 180 degree
            maze_solving(1);
          }
          return;
        }
      }
      delay(node_delay); reading();
      if (sum != 0) cross = side;
      (side == 'l') ? path[counter] = 1 : path[counter] = 3;
      counter++; digitalWrite(light, HIGH);
      m1 = millis();
    }
    if (millis() - m1 > 500) flag = 's'; digitalWrite(light, LOW);
  }
}
