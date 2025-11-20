int stringFormatSize(char * string) {
	int i = 0, n = 0, total = 0;
	LeitorDeFormato leitor = FORA_DO_FORMATO;
	while (string[i] != '\0') {
		switch (leitor) {
			case FORA_DO_FORMATO:
				if (string[i] == '%') {
					leitor = LENDO_FORMATO;
					n--;
				}	
				break;
			case LENDO_FORMATO:
				if (string[i] >= '0' && string[i] <= '9') {
					total *= 10;
					total += string[i]-'0';
					n--;
				} else {
					n += total-1;
					total = 0;
					leitor = SAINDO_DO_FORMATO;
				}
				break;
			case SAINDO_DO_FORMATO:
				if (string[i] == ' ')
					leitor = FORA_DO_FORMATO;
				else if (string[i] == '%')
					leitor = LENDO_FORMATO;
				else
					n--;
				break;
		}
		i++;
		n++;
	}
	return n;
}
