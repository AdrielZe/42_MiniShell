# 42_MiniShell

<h2>Sobre o Projeto</h2>
<p>
    O <strong>Minishell</strong> é um projeto da 42 que tem como objetivo criar um pequeno interpretador de comandos baseado no Bash. O desafio principal é implementar funcionalidades de um shell real, garantindo conformidade com comportamentos práticos e padrões POSIX, ao mesmo tempo em que aprendemos mais sobre sistemas operacionais e comunicação entre processos.
</p>
<p>
    Este repositório foi criado para documentar e organizar o desenvolvimento do projeto, que está sendo feito de forma colaborativa e seguindo boas práticas de programação.
</p>

<hr>

<h2>Funcionalidades Requeridas</h2>
<ul>
    <li>Implementar um prompt que aceite e execute comandos.</li>
    <li>Suporte às seguintes funcionalidades do Bash:
        <ul>
            <li>Execução de comandos com argumentos.</li>
            <li>Suporte a redirecionamentos (<code>&gt;</code>, <code>&gt;&gt;</code>, <code>&lt;</code>).</li>
            <li>Pipes (<code>|</code>).</li>
            <li>Variáveis de ambiente.</li>
            <li>Expansão de variáveis e caracteres especiais (<code>$</code>, <code>~</code>).</li>
            <li>Tratamento de sinais (<code>Ctrl+C</code>, <code>Ctrl+D</code>, <code>Ctrl+\</code>).</li>
        </ul>
    </li>
    <li>Implementar builtins:
        <ul>
            <li><code>echo</code></li>
            <li><code>cd</code></li>
            <li><code>pwd</code></li>
            <li><code>export</code></li>
            <li><code>unset</code></li>
            <li><code>env</code></li>
            <li><code>exit</code></li>
        </ul>
    </li>
    <li>Gerenciamento de erros:
        <ul>
            <li>Mensagens de erro amigáveis para comandos inválidos ou erros de sintaxe.</li>
            <li>Sinalização de saída apropriada (status de retorno).</li>
        </ul>
    </li>
</ul>

<hr>

<h2>Tecnologias e Ferramentas</h2>
<ul>
    <li>Linguagem: <strong>C</strong></li>
    <li>Sistema operacional: <strong>Linux</strong></li>
    <li>Bibliotecas:
        <ul>
            <li><code>readline</code> para manipulação de entrada de usuário.</li>
            <li>Funções da biblioteca padrão POSIX.</li>
        </ul>
    </li>
</ul>

<hr>

<h2>Como Compilar</h2>
<p>
    Para compilar o projeto, certifique-se de ter o compilador <strong>gcc</strong> e o <strong>Make</strong> instalados. Use o seguinte comando:
</p>
<pre><code>make</code></pre>
<p>O binário será gerado na raiz do projeto com o nome <code>minishell</code>.</p>

<hr>
