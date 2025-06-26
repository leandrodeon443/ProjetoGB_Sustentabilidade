# 🌿 Projeto Sustentabilidade - Grau B

### 👥 Grupo:
- Gustavo Dosso  
- Leandro Deon  
- Lucas Pontes  

---

## 🧩 Quiz da Sustentabilidade

Este programa é um **quiz interativo em linguagem C**, com 20 perguntas relacionadas à:

- 🌱 Sustentabilidade  
- 🌍 Meio ambiente  
- 🛍️ Consumo consciente  
- 🧑‍🤝‍🧑 Responsabilidade social  

As perguntas e alternativas são **embaralhadas** a cada execução, tornando o jogo mais dinâmico e imprevisível. O programa também **coleta dados do participante** (como idade, cidade e escolaridade) e armazena essas informações em um arquivo.

---

## 🎯 Funcionalidades

- Coleta de dados pessoais com validação de entrada
- Embaralhamento aleatório de perguntas e alternativas
- Pontuação automática com somatória ao final do quiz
- Uso de **cores ANSI** para destacar respostas corretas/erradas
- Exibição de **banners ASCII** estilizados
- Suporte a caracteres especiais (UTF-8)
- Registro completo em arquivo `database.txt`

---

## 💻 Tecnologias e Recursos Usados

- Linguagem **C**
- `stdio.h`, `stdlib.h`, `string.h`, `ctype.h`, `locale.h`, `time.h`
- `windows.h` ou `unistd.h` para compatibilidade com Windows e Linux
- `setlocale()` para acentuação UTF-8
- `fgets()` e validação de strings para entrada segura

---

## ⚙️ Execução

### 🐧 Linux/macOS:
```bash
gcc main.c -o quiz
./quiz
```

### 🪟 Windows
```PowerShell
gcc main.c -o quiz.exe
.\quiz.exe
```


## 🗂️ Registro de Dados

Os dados do usuário e o resultado do quiz são salvos automaticamente em um arquivo chamado database.txt. Exemplo de entrada:

```txt
[2025-06-26 | 14:35]
Idade: 22
Cidade: Campinas
Gênero: Feminino
Escolaridade: Ensino Médio
Ocupação: Estudante
Frequência de Internet: Diariamente
Participação Ambiental: Sim, projetos na escola
```

## Bibliografia

https://stackoverflow.com/questions/18047409/how-do-you-output-a-banner-every-10-lines

https://stackoverflow.com/questions/27878570/c-ifdef-else-endif-directives

https://stackoverflow.com/questions/8666378/detect-windows-or-linux-in-c-c

https://www.w3schools.com/c/c_structs.php

https://www.cprogramming.com/tutorial/unicode.html

https://www.generacodice.com/pt/articolo/364244/a-formata-o-de-texto-em-ruby-para-a-embalagem-desliza

http://prorum.com/?qa=2547/como-justificar-texto-usando-programacao-dinâmica

https://www.nerdfonts.com/

https://gist.github.com/XVilka/8346728

https://stackoverflow.com/questions/1489183/how-can-i-use-ruby-to-colorize-the-text-output-to-a-terminal

https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#extended-colors