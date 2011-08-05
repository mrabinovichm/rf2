
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                            %
%                      UNIVERSIDAD NACIONAL DE INGENIARA                     %
%               Facultad de Ingeniera Industrial y de Sistemas               %
%                                                                            %
%                              ------------------                            %
%                             | FORMATO DE TESIS |                           %
%                              ------------------                            %
%                                                                            %
%                           (C) Samuel Oporto Daz                            %
%                         (C) Brucele Tejeda Medrano                         %
%                                                                            %
%                                     2006                                   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Declaramos la plantilla

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{rf2}[2006/09/20 v1.0 Universidad Nacional de Ingeniera]
\RequirePackage{fancyhdr}
%\RequirePackage{ifthen}



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% OPCIONES: Son las opciones principales del documento %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


\newcommand\@ptsize{}
\newcommand\@draftmark{}
\newif\if@tept
\newif\if@elpt
\newif\if@twpt
\newif\if@dbl
\if@compatibility\else
\DeclareOption{a4paper}
   {\setlength\paperheight {297mm}%
    \setlength\paperwidth  {210mm}}
\DeclareOption{a5paper}
   {\setlength\paperheight {210mm}%
    \setlength\paperwidth  {148mm}}
\DeclareOption{b5paper}
   {\setlength\paperheight {250mm}%
    \setlength\paperwidth  {176mm}}
\DeclareOption{letterpaper}
   {\setlength\paperheight {11in}%
    \setlength\paperwidth  {8.5in}}
\DeclareOption{legalpaper}
   {\setlength\paperheight {14in}%
    \setlength\paperwidth  {8.5in}}
\DeclareOption{executivepaper}
   {\setlength\paperheight {10.5in}%
    \setlength\paperwidth  {7.25in}}
\DeclareOption{landscape}
   {\setlength\@tempdima   {\paperheight}%
    \setlength\paperheight {\paperwidth}%
    \setlength\paperwidth  {\@tempdima}}
\fi
\DeclareOption{10pt}{\renewcommand\@ptsize{0} \@tepttrue}
\DeclareOption{11pt}{\renewcommand\@ptsize{1} \@elpttrue}
\DeclareOption{12pt}{\renewcommand\@ptsize{2} \@twpttrue}
\DeclareOption{oneside}{\@twosidefalse \@mparswitchfalse}
\DeclareOption{twoside}{\@twosidetrue  \@mparswitchtrue}
\DeclareOption{doublespace}{\@dbltrue}
\DeclareOption{draft}{\renewcommand\@draftmark{1}}
\DeclareOption{final}{\renewcommand\@draftmark{0}}
\ExecuteOptions{letterpaper,11pt,oneside,final}



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% elegimos EL TIPO Y TAMAÑO %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% 10pt : hutT10, 11pt : hut11, 12pt : hut12


%  Impresión SIMPLE o DOBLE.

% \@twosidefalse               %  Por default es one-sided.
\def\ds@twoside{\@twosidetrue  %  Definir la opción twoside.
           \@mparswitchtrue}   %


% Doble columna
\def\ds@twocolumn{\@twocolumntrue}


\ProcessOptions

% Carga del tamaño
\input {Fuente/hut1\@ptsize.clo}

\relax





% Espacios simple
\def\ssp{\def\baselinestretch{1.0}\large\normalsize}

% Espacios dobles
\def\dsp{\def\baselinestretch{1.8}\large\normalsize}
\def\hsp{\def\baselinestretch{1.37}\large\normalsize} % intermediate spacing

% Sangría
\def\smallssp{\def\baselinestretch{1.0}\large\small}
\def\scriptsizessp{\def\baselinestretch{1.0}\large\scriptsize}


% Cajas
% \overfullrule = 0pt
\ifnum \@draftmark = 1
\if@dbl
\dsp
\else
\ssp
\fi
\overfullrule 5pt
\fi



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% PARA USAR LAS PALABRAS AUTOMÁTICAS EN ESPAÑOL %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% \tableofcontents:
\def\contentsname{Contenido}
%
% \listoffigures:
\def\listfigurename{Lista de Figuras}
%
% \listoftables:
\def\listtablename{Lista de Tablas}
%
% \thebibliography:
\def\bibname{Bibliograf\'{\i}a}
%
% \theindex:
\def\indexname{\'{I}ndice}
%
% Figuras
\def\figurename{Figura}
%
% Tablas
\def\tablename{Tabla}
%
% \chapter:
\def\chaptername{Cap\'{\i}tulo}
%
% \appendix:
\def\appendixname{Ap\'{e}ndice}
%
% \part
\def\partname{Parte}
%
% abstract
\def\abstractname{Resumen}
%
% Agradecimientos
\def\acknowledgename{Agradecimientos}
%
% Citas previas del trabajo
\def\citationname{Citas de trabajos previos publicados}
%



%%%%%%%%%%%
% FUENTE %
%%%%%%%%%%%



% Año y mes
\def\degreeyear#1{\gdef\@degreeyear{#1}}
\def\degreemonth#1{\gdef\@degreemonth{#1}}

% Grado
\def\degree#1{\gdef\@degree{#1}}

% Nombre del asesor
\def\advisor#1{\gdef\@advisor{#1}}

\def\alwayssingle{\@restonecolfalse\if@twocolumn\@restonecoltrue\onecolumn
     \else \newpage \fi}

\def\endalwayssingle{\if@restonecol\twocolumn \else \newpage \fi}




% Conjunto de fuentes
\def\fmfont{\fontsize\@xiipt{14.5}\selectfont}
\def\fmsmallfont{\fontsize\@xiipt{14pt}\selectfont}




\def\maketitle{
{
    \pagenumbering{roman}
    \hsp
  \newpage
  \thispagestyle{empty}
  \addcontentsline{toc}{section}{T\'itulo}
  \centerline{\ }
  \centerline{\LARGE \bf Universidad de la Rep\'ublica}
  \centerline{\large \bf Facultad de Ingenier\'ia}
  \centerline{\ }


\vspace{0.4in}
  \begin{center}
    {\large Proyecto de fin de carrera}
  \end{center}
  \centerline{\ }
  \centerline{\ }

  \centerline{\ }

  \centerline{\LARGE Recarga F\'acil por Radio Frecuencia}  
  \centerline{\ }
  \centerline{\LARGE\bf {\@title}}  
%  \centerline{\ }
%  \centerline{\ }
  \medskip

\centerline{\ }
  \medskip
%\begin{figure}[h]
% \centering
% \includegraphics[scale=.25]{Imagenes/Foto.jpg}
%\end{figure}

  \centerline{\ }
  \centerline{\ }
  \centerline{\ }
  \centerline{\ }

  \centerline{\ }
  \centerline{\ }
  \centerline{\large\bf \@author}
  \centerline{\ }
  \centerline{\ }
  \centerline{Tutores: \large \@advisor}
  \centerline{\ }
  \centerline{\ }
  \centerline{Montevideo, Uruguay}
  \centerline{{\@degreemonth} {\@degreeyear}}
  \setcounter{footnote}{0}
  }
}

%%%%%%%%%%%%%
% COPYRIGHT %
%%%%%%%%%%%%%


\def\copyrightpage
{
  \newpage
  \thispagestyle{empty}
  \rule[0pt]{0pt}{0pt} \\
  \vspace{2.5in}
  \rule[0pt]{0pt}{0pt} \\
  \centerline{\copyright {\@degreeyear} - {\@author}}
  \centerline{\ }
  \centerline{Todos los derechos reservados.}
}


%%%%%%%%%%%%
% ABSTRACT %
%%%%%%%%%%%%

\newenvironment{abstract}
{
  \newpage
  \thispagestyle{plain}
    \@mkboth{\abstractname}{\abstractname}
  \addcontentsline{toc}{section}{Resumen}
    %%%%%\vspace*{.5in}
    %%%%%\noindent Asesor de tesis \hfill Autor \\
    %%%%%\noindent {\bf \@advisor} \hfill {\bf \@author} \\[.4in]
    \centerline{\large\bf Recarga F\'acil por Radio Frecuencia}%{\@title}}
    \bigskip
    \bigskip
  \centerline{\bf {\LARGE Resumen}}
   \bigskip
}
{}




\newenvironment{engabstract}
{
  \newpage
  \thispagestyle{plain}
    \@mkboth{\abstractname}{\abstractname}
  \addcontentsline{toc}{section}{Abstract}
    %%%%%\vspace*{-.7in}
    %%%%%\noindent Thesis advisor \hfill Author \\
    %%%%%\noindent {\bf \@advisor} \hfill {\bf \@author} \\[.5in]
    \centerline{\large \bf {\@engtitle}}
    \bigskip
    \bigskip
  \centerline{\bf {\LARGE Abstract}}
  \bigskip
}
{}









%%%%%%%%%%%%%%%
% DEDICATORIA %
%%%%%%%%%%%%%%%



\newenvironment{dedication}
{
  \newpage
  \thispagestyle{plain}
  \addcontentsline{toc}{section}{Dedicatoria}
}
{}

%%%%%%%%%%%%%%%%%%%
% 	  PREFACIO	  %
%%%%%%%%%%%%%%%%%%%
\newenvironment{prefacio}
{
  \newpage
  \thispagestyle{plain}
    \@mkboth{\acknowledgename}{\acknowledgename}
  \addcontentsline{toc}{section}{Prefacio}
  %\vspace*{.8in}
  {\centering{\bf {\large Prefacio}}}
  \vspace*{.2in}
}

%%%%%%%%%%%%%%%%%%%
% AGRADECIMIENTOS %
%%%%%%%%%%%%%%%%%%%


\newenvironment{acknowledgments}
{
  \newpage
  \thispagestyle{plain}
    \@mkboth{\acknowledgename}{\acknowledgename}
  \addcontentsline{toc}{section}{Agradecimientos}
  %\vspace*{.8in}
  {\rightline{\bf {\large Agradecimientos}}}
  \vspace*{.2in}
}
{}

%%%%%%%%%%%%%%%%%%%
% CITAS INICIALES %
%%%%%%%%%%%%%%%%%%%

\newenvironment{citations}
{
  \newpage
  \thispagestyle{plain}
  \addcontentsline{toc}{section}{\citationname}
  \vspace*{-.8in}
  {\centerline{\bf {\LARGE \citationname}}}
  \vspace*{.2in}
}
{}


% Recomenzar el comando de numaración de páginas
\newenvironment{startarabicpagination}
{
    \setcounter{page}{1}
    \pagenumbering{arabic}
}
{}



%%%%%%%%%%
% LISTAS %
%%%%%%%%%%

% ENUMERATE
\def\labelenumi{\theenumi.}
\def\theenumi{\arabic{enumi}}

\def\labelenumii{(\theenumii)}
\def\theenumii{\alph{enumii}}
\def\p@enumii{\theenumi}

\def\labelenumiii{\theenumiii.}
\def\theenumiii{\roman{enumiii}}
\def\p@enumiii{\theenumi(\theenumii)}

\def\labelenumiv{\theenumiv.}
\def\theenumiv{\Alph{enumiv}}
\def\p@enumiv{\p@enumiii\theenumiii}

% ITEMIZE
\def\labelitemi{$\m@th\bullet$}
\def\labelitemii{\bfseries --}
\def\labelitemiii{$\m@th\ast$}
\def\labelitemiv{$\m@th\cdot$}


% VERSOS
\def\verse{\par\let\\=\@centercr
  \list{}{\ssp\itemsep\z@ \itemindent -1.5em\listparindent \itemindent
          \rightmargin\leftmargin\advance\leftmargin 1.5em}\item[]}
\let\endverse\endlist


% QUOTATION
\def\quotation{\par\list{}{\ssp\listparindent 1.5em
    \itemindent\listparindent
    \rightmargin\leftmargin\parsep \z@ plus\p@}\item[]}
\let\endquotation=\endlist

% QUOTE
\def\quote{\par\list{}{\ssp\rightmargin\leftmargin}\item[]}
\let\endquote=\endlist

% DESCRIPTION
%  \descriptionlabel.

\def\descriptionlabel#1{\hspace\labelsep \bfseries #1}
\def\description{\list{}{\labelwidth\z@ \itemindent-\leftmargin
       \let\makelabel\descriptionlabel}}

\let\enddescription\endlist

\newdimen\descriptionmargin
\descriptionmargin=3em


%%%%%%%%%
% OTROS %
%%%%%%%%%


\def\@verbatim{\trivlist\ssp \item[]\if@minipage\else\vskip\parskip\fi
\leftskip\@totalleftmargin\rightskip\z@
\parindent\z@\parfillskip\@flushglue\parskip\z@

\@@par
\@tempswafalse \def\par{\if@tempswa\hbox{}\fi\@tempswatrue\@@par
\penalty\interlinepenalty}%
\obeylines \ttfamily \catcode``=13 \@noligs \let\do\@makeother \dospecials}



% ARRAY Y TABULAR

\arraycolsep 5pt

\tabcolsep 6pt

\arrayrulewidth .4pt
\doublerulesep 2pt


\def\array{\let\@acol\@arrayacol \let\@classz\@arrayclassz
 \let\@classiv\@arrayclassiv \let\\\@arraycr\let\@halignto\@empty\@tabarray}


\tabbingsep \labelsep



\def\tabular{\par\ssp\let\@halignto\@empty\@tabular}
\expandafter \def\csname tabular*\endcsname #1%
{\par\ssp\def\@halignto{to#1}\@tabular}


\def\smalltabular{\par\smallssp\let\@halignto\@empty\@tabular}
\def\endsmalltabular{\endtabular}
\expandafter \def\csname smalltabular*\endcsname #1%
{\par\smallssp\def\@halignto{to#1}\@tabular}
\expandafter \let \csname endsmalltabular*\endcsname = \endtabular


\def\scriptsizetabular{\par\scriptsizessp\let\@halignto\@empty\@tabular}
\def\endscriptsizetabular{\endtabular}
\expandafter \def\csname scriptsizetabular*\endcsname #1%
{\par\scriptsizessp\def\@halignto{to#1}\@tabular}
\expandafter \let \csname endscriptsizetabular*\endcsname = \endtabular

% MINIPAGE
\skip\@mpfootins = \skip\footins

% FRAMEBOX
\fboxsep = 3pt

\fboxrule = .4pt



%%%%%%%%%%%%%%%%%%%%%%%%%
% CAPÍTULOS Y SECCIONES %
%%%%%%%%%%%%%%%%%%%%%%%%%

\def\@startsection#1#2#3#4#5#6{\if@noskipsec \leavevmode \fi
   \par \@tempskipa #4\relax
   \@afterindenttrue
   \ifdim \@tempskipa <\z@ \@tempskipa -\@tempskipa \relax\fi
   \if@nobreak \everypar{}\else
     \addpenalty{\@secpenalty}\addvspace{\@tempskipa}\fi \@ifstar
     {\@ssect{#3}{#4}{#5}{#6}}{\@dblarg{\@sect{#1}{#2}{#3}{#4}{#5}{#6}}}}

\newcounter {part}
\newcounter {chapter}
\newcounter {section}[chapter]
\newcounter {subsection}[section]
\newcounter {subsubsection}[subsection]
\newcounter {paragraph}[subsubsection]
\newcounter {subparagraph}[paragraph]



\def\thepart          {\Roman{part}}
\def\thechapter       {\arabic{chapter}}
\def\thesection       {\thechapter.\arabic{section}}
\def\thesubsection    {\thesection.\arabic{subsection}}
\def\thesubsubsection {\thesubsection .\arabic{subsubsection}}
\def\theparagraph     {\thesubsubsection.\arabic{paragraph}}
\def\thesubparagraph  {\theparagraph.\arabic{subparagraph}}


\def\@chapapp{\chaptername}

%%%%%%%%%%
%  PARTE %
%%%%%%%%%%

\def\part{\cleardoublepage
   \thispagestyle{plain}%
  \if@twocolumn
     \onecolumn
     \@tempswatrue
    \else \@tempswafalse
  \fi
  \hbox{}\vfil
%%  \bgroup  \centering
  \secdef\@part\@spart}

\def\@part[#1]#2{\ifnum \c@secnumdepth >-2\relax
        \refstepcounter{part}%

        \addcontentsline{toc}{part}{\thepart
        \hspace{1em}#1}\else

        \addcontentsline{toc}{part}{#1}\fi
   \markboth{}{}%
   {\centering
    \interlinepenalty \@M
    \ifnum \c@secnumdepth >-2\relax
      \huge\bfseries \partname~\thepart
    \par
    \vskip 20\p@\fi
    \Huge \bfseries
    #2\par}\@endpart}



\def\@endpart{\vfil\newpage
   \if@twoside
       \hbox{}%
       \thispagestyle{empty}%
       \newpage
   \fi
   \if@tempswa
     \twocolumn
   \fi}

\def\@spart#1{{\centering
   \interlinepenalty \@M
   \Huge \bfseries
   #1\par}\@endpart}





%    ****************************************
%    *         TABLE OF CONTENTS, ETC.      *
%    ****************************************

%%%%%%%%%%%%%%%%%%%%%%%
% TABLA DE CONTENIDOS %
%%%%%%%%%%%%%%%%%%%%%%%

\def\@pnumwidth{1.55em}
\def\@tocrmarg {2.55em}
\def\@dotsep{4.5}
\setcounter{tocdepth}{4}


% TABLEOFCONTENTS

\def\tableofcontents{\@restonecolfalse
  \if@twocolumn\@restonecoltrue\onecolumn\fi
  \chapter*{\contentsname
        \@mkboth{\uppercase{\contentsname}}{\uppercase{\contentsname}}}%
  {\ssp\@starttoc{toc}}\if@restonecol\twocolumn\fi}

\def\l@part#1#2{\addpenalty{-\@highpenalty}%
   \addvspace{2.25em plus\p@}
   \begingroup
   \@tempdima 3em
     \parindent \z@ \rightskip \@pnumwidth
     \parfillskip -\@pnumwidth
     {\large \bfseries
     \leavevmode
     #1\hfil \hbox to\@pnumwidth{\hss #2}}\par
     \nobreak
    \global\@nobreaktrue
    \everypar{\global\@nobreakfalse\everypar{}}

   \endgroup}



\def\l@chapter#1#2{\addpenalty{-\@highpenalty}%
   \vskip 1.0em plus\p@   % space above chapter line
   \@tempdima 1.5em       % width of box holding chapter number
   \begingroup
     \parindent \z@ \rightskip \@pnumwidth
     \parfillskip -\@pnumwidth
     \bfseries                  % Boldface.
     \leavevmode          % TeX command to enter horizontal mode.
      \advance\leftskip\@tempdima  %% added 5 Feb 88 to conform to
      \hskip -\leftskip            %% 25 Jan 88 change to \numberline
     #1\nobreak\hfil \nobreak\hbox to\@pnumwidth{\hss #2}\par
     \penalty\@highpenalty %% added 24 May 89, suggested by J. Leichter
   \endgroup}

\def\l@section{\@dottedtocline{1}{1.5em}{2.3em}}
\def\l@subsection{\@dottedtocline{2}{3.8em}{3.2em}}
\def\l@subsubsection{\@dottedtocline{3}{7.0em}{4.1em}}
\def\l@paragraph{\@dottedtocline{4}{10em}{5em}}
\def\l@subparagraph{\@dottedtocline{5}{12em}{6em}}



%%%%%%%%%%%%%%%%%%%%
% LISTA DE FIGURAS %
%%%%%%%%%%%%%%%%%%%%


\def\listoffigures{\@restonecolfalse
  \if@twocolumn\@restonecoltrue\onecolumn\fi
  \chapter*{\listfigurename\@mkboth{\uppercase{\listfigurename}}%
{\uppercase{\listfigurename}}}
   \addcontentsline{toc}{section}{\listfigurename}
   {\ssp\@starttoc{lof}}\if@restonecol
    \twocolumn\fi}

\def\l@figure{\@dottedtocline{1}{1.5em}{2.3em}}


%%%%%%%%%%%%%%%%%%%
% LISTA DE TABLAS %
%%%%%%%%%%%%%%%%%%%


\def\listoftables{\@restonecolfalse
  \if@twocolumn\@restonecoltrue\onecolumn\fi
  \chapter*{\listtablename\@mkboth{\uppercase{\listtablename}}%
   {\uppercase{\listtablename}}}\@starttoc{lot}\if@restonecol
  \twocolumn\fi}
\def\listoftables{\@restonecolfalse
  \if@twocolumn\@restonecoltrue\onecolumn\fi
  \chapter*{\listtablename\@mkboth{\uppercase{\listtablename}}%
{\uppercase{\listtablename}}}
   \addcontentsline{toc}{section}{\listtablename}
   {\ssp\@starttoc{lot}}\if@restonecol
  \twocolumn\fi}


\let\l@table\l@figure



%%%%%%%%%%%%%%%%
% BIBLIOGRAFIA %
%%%%%%%%%%%%%%%%

\def\thebibliography#1{\chapter*{\bibname\@mkboth
  {\uppercase{\bibname}}{\uppercase{\bibname}}}
  \addcontentsline{toc}{chapter}{\bibname}
  \list{\@biblabel{\arabic{enumiv}}}{\settowidth\labelwidth{\@biblabel{#1}}%
    \leftmargin\labelwidth
    \advance\leftmargin\labelsep
    \usecounter{enumiv}%
    \let\p@enumiv\@empty
    \def\theenumiv{\arabic{enumiv}}}%
    \def\newblock{\hskip .11em plus.33em minus.07em}%
    \sloppy\clubpenalty4000\widowpenalty4000
    \sfcode`\.=\@m}



\def\endthebibliography{%
  \def\@noitemerr{\@warning{Empty `thebibliography' environment}}%
  \endlist}


%%%%%%%%%%
% INDICE %
%%%%%%%%%%



\newif\if@restonecol

\def\theindex{\@restonecoltrue\if@twocolumn\@restonecolfalse\fi
\columnseprule \z@
\columnsep 35\p@\twocolumn[\@makeschapterhead{\indexname}]%
    \@mkboth{\uppercase{\indexname}}{\uppercase{\indexname}}%
    \thispagestyle{plain}\parindent\z@
    \parskip\z@ plus .3\p@\relax\let\item\@idxitem}

\def\@idxitem{\par\hangindent 40\p@}

\def\subitem{\par\hangindent 40\p@ \hspace*{20\p@}}

\def\subsubitem{\par\hangindent 40\p@ \hspace*{30\p@}}

\def\endtheindex{\if@restonecol\onecolumn\else\clearpage\fi}

\def\indexspace{\par \vskip 10\p@ plus5\p@ minus3\p@\relax}


%%%%%%%%%%%%%
% FOOTNOTES %
%%%%%%%%%%%%%



\def\footnoterule{\kern-3\p@
  \hrule width .4\columnwidth
  \kern 2.6\p@}                 % The \hrule has default height of .4pt.

% \newcounter{footnote}
\@addtoreset{footnote}{chapter}  % Numbers footnotes within chapters



\long\def\@makefntext#1{\parindent 1em\noindent
            \hbox to 1.8em{\hss$\m@th^{\@thefnmark}$}#1}


\long\def\@footnotetext#1{\insert\footins{\ssp\reset@font\footnotesize
    \interlinepenalty\interfootnotelinepenalty
    \splittopskip\footnotesep
    \splitmaxdepth \dp\strutbox \floatingpenalty \@MM
    \hsize\columnwidth \@parboxrestore
   \edef\@currentlabel{\csname p@footnote\endcsname\@thefnmark}\@makefntext
    {\rule{\z@}{\footnotesep}\ignorespaces
      #1\strut}}}



%%%%%%%%%%%%%%%%%%%%
% FIGURAS Y TABLAS %
%%%%%%%%%%%%%%%%%%%%

\setcounter{topnumber}{2}
\def\topfraction{.7}
\setcounter{bottomnumber}{1}
\def\bottomfraction{.3}
\setcounter{totalnumber}{3}
\def\textfraction{.2}
\def\floatpagefraction{.5}
\setcounter{dbltopnumber}{2}
\def\dbltopfraction{.7}
\def\dblfloatpagefraction{.5}


\long\def\@makecaption#1#2{% Add space only if something is ...
   \par\ifdim\prevdepth>-\p@ \vskip 10\p@\relax \fi % above the caption
   \setbox\@tempboxa\hbox{\vbox to\topskip{}#1: #2\unskip\strut}%
   \ifdim \wd\@tempboxa >\hsize      % IF longer than one line:
       {\ssp#1: #2\unskip\strut\par} %   THEN set as ordinary paragraph.
     \else                           %   ELSE  center.
       \hbox to\hsize{\hfil\unhbox\@tempboxa\hfil}%
   \fi}



\newcounter{figure}[chapter]
\def\thefigure{\thechapter.\@arabic\c@figure}

\def\fps@figure{tbp}
\def\ftype@figure{1}
\def\ext@figure{lof}
\def\fnum@figure{\figurename~\thefigure}
\def\figure{\@float{figure}}

\def\endfigure{\end@float}
\@namedef{figure*}{\@dblfloat{figure}}
\@namedef{endfigure*}{\end@dblfloat}


\newcounter{table}[chapter]
\def\thetable{\thechapter.\@arabic\c@table}

\def\fps@table{tbp}
\def\ftype@table{2}
\def\ext@table{lot}
\def\fnum@table{\tablename~\thetable}
\def\table{\@float{table}}

\def\endtable{\end@float}
\@namedef{table*}{\@dblfloat{table}}
\@namedef{endtable*}{\end@dblfloat}



%%%%%%%%%%%%%%%%%%%
% STILO DE PÁGINA %
%%%%%%%%%%%%%%%%%%%



\mark{{}{}}   % Initializes TeX's marks



\if@twoside         % If two-sided printing.
\def\ps@headings{\let\@mkboth\markboth
 \def\@oddfoot{}\def\@evenfoot{}%       No feet.
 \def\@evenhead{\rmfamily \thepage\hfil \slshape \leftmark}%    Left heading.
 \def\@oddhead{{\slshape \rightmark}\hfil \rmfamily\thepage}% Right heading.
 \def\chaptermark##1{\markboth {\uppercase{\ifnum \c@secnumdepth >\m@ne
      \@chapapp\ \thechapter. \ \fi ##1}}{}}%
 \def\sectionmark##1{\markright {\uppercase{\ifnum \c@secnumdepth >\z@
   \thesection. \ \fi ##1}}}}
\else               % If one-sided printing.
\def\ps@headings{\let\@mkboth\markboth
\def\@oddfoot{}\def\@evenfoot{}%     No feet.
\def\@oddhead{{\slshape \rightmark}\hfil \rmfamily\thepage}% Heading.
\def\chaptermark##1{\markright {\uppercase{\ifnum \c@secnumdepth >\m@ne
  \@chapapp\ \thechapter. \ \fi ##1}}}}
\fi



\def\ps@myheadings{\let\@mkboth\@gobbletwo
 \def\@oddhead{{\slshape\rightmark}\hfil \rmfamily\thepage}%
 \def\@oddfoot{}\def\@evenhead{\rmfamily \thepage\hfil\slshape\leftmark}%
 \def\@evenfoot{}\def\chaptermark##1{}\def\sectionmark##1{}%
 \def\subsectionmark##1{}}








\def\today{\ifcase\month\or
  January\or February\or March\or April\or May\or June\or
  July\or August\or September\or October\or November\or December\fi
  \space\number\day, \number\year}


\@addtoreset{equation}{chapter}


\def\theequation{\thechapter.\arabic{equation}}




%%%%%%%%%%%%%%%%%%
% INITIALIZATION %
%%%%%%%%%%%%%%%%%%
\textwidth 5.8in


\ps@plain
\pagenumbering{arabic}
\if@twoside\else\raggedbottom\fi

\if@twocolumn
 \@@input twocolum.sty\relax
\else
 \onecolumn
\fi


\pagestyle{fancy}

\renewcommand{\chaptermark}[1]{\markboth{\@chapapp\ \thechapter:\ #1}{}}

\fancyhf{}
\renewcommand{\headrulewidth}{0.4pt}
\renewcommand{\footrulewidth}{0pt}

\if@twoside
\ifnum \@draftmark = 1
\fancyhead[LO,RE]{
  \nouppercase{\itshape \leftmark}\hspace{.2in} {\bfseries DRAFT}}
\else
\fancyhead[LO,RE]{\nouppercase{\itshape \leftmark}}
\fi
\fancyhead[RO,LE]{\thepage}
\else
\ifnum \@draftmark = 1
\fancyhead[LE,LO]{
  \nouppercase{\itshape \leftmark}\hspace{.2in} {\bfseries DRAFT}}
\else
\fancyhead[LE,LO]{\nouppercase{\itshape \leftmark}}
\fi
\fancyhead[RE,RO]{\thepage}
\fi

\fancypagestyle{plain}{
  \fancyhf{}
  \fancyfoot[C]{\thepage}
  \renewcommand{\headrulewidth}{0pt}
  \renewcommand{\footrulewidth}{0pt}
}

\newcommand{\shortchap}{}
\newcommand{\hackchapter}[2]{
  \renewcommand{\shortchap}{\itshape \large \@chapapp \thechapter:  #2}
  \chapter{#1}
}


% 10 pt
\if@tept
\addtolength{\textheight}{-.4in} % this seems a hack
\setlength{\headwidth}{\textwidth}
\fi

% 11 pt
\if@elpt
%\addtolength{\textheight}{0.2in} % this seems a hack
\setlength{\headwidth}{\textwidth}
\addtolength{\headheight}{2pt}
\fi

% 12 pt
\if@twpt
\addtolength{\textheight}{.4in}
\setlength{\headwidth}{\textwidth}
\fi


%\setlength{\topmargin}{0.03in}
\setlength{\topmargin}{0in}
\setlength{\oddsidemargin}{.5in}
\textwidth 5.8in


\setlength{\parindent}{17pt}

\bibliographystyle{ieeetr}

\endinput
