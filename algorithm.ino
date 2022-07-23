void algorithm() {
  int s = 0, a = 0;
  if (side == 'r') {
    while (1) {
      if (path[a] == 3) path[a] = 1;
      else if (path[a] == 1) path[a] = 3;
      else if (path[a] == 5) break;
      a++;
    }
  }
  a = 0;
  while (1) {
    if (path[a + 1] == 4) {
      a += 2;  path[s] = path[s] + path[a];
    }
    if (path[s] == 4) {
      s--; a++;  path[s] = path[s] + path[a];
    }
    else {
      s++; a++;  path[s] = path[a];
    }
    if (path[s] == 5) break;
  }
  if (side == 'r') {
    a = 0;
    while (1) {
      if (path[a] == 3) path[a] = 1;
      else if (path[a] == 1) path[a] = 3;
      else if (path[a] == 5) break;
      a++;
    }
  }
}
