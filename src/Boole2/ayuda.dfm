object fAyuda: TfAyuda
  Left = 201
  Top = 159
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Ayuda de Circuitos Secuenciales'
  ClientHeight = 504
  ClientWidth = 672
  Color = clWindow
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 440
    Top = 296
    Width = 145
    Height = 20
    Alignment = taCenter
    Caption = 'Automatas de Mealy'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 112
    Top = 296
    Width = 149
    Height = 20
    Alignment = taCenter
    Caption = 'Automatas de Moore'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object StaticText1: TStaticText
    Left = 72
    Top = 192
    Width = 4
    Height = 4
    TabOrder = 0
  end
  object Memo1: TMemo
    Left = 80
    Top = 320
    Width = 217
    Height = 97
    BorderStyle = bsNone
    Lines.Strings = (
      'ESTADOS: En la etiqueta hay que especificar '
      'un nombre y la salida correspondiente al '
      'estado.'
      ''
      'TRANSICIONES: En la etiqueta hay que '
      'especificar los valores de entrada que '
      'provocan la transici�n.')
    ReadOnly = True
    TabOrder = 1
  end
  object Memo2: TMemo
    Left = 392
    Top = 320
    Width = 233
    Height = 97
    BorderStyle = bsNone
    Lines.Strings = (
      'ESTADOS: En la etiqueta hay que especificar un '
      'nombre.'
      ''
      'TRANSICIONES: En la etiqueta hay que '
      'especificar los valores de entrada que provocan '
      'la transici�n, y los valores de salida producidos al '
      'provocarse la transici�n.')
    ReadOnly = True
    TabOrder = 2
  end
  object Memo3: TMemo
    Left = 24
    Top = 48
    Width = 625
    Height = 241
    BorderStyle = bsNone
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Lines.Strings = (
      
        'Una vez creado el automata, es necesario definir sus estados y s' +
        'us transiciones. En BOOLE esto se consigue '#39'dibujandolos'#39' sobre ' +
        'la '
      
        'ventana de Sistemas Secuenciales. Antes de nada, hay que asegura' +
        'rse de que est� activa la barra de herramientas (una paleta con '
      
        'botones para seleccionar y crear estados y transiciones). Si no ' +
        'lo est�, vaya al men� "Ver" y haga click en la opci�n "Barra de '
      'Herramientas"'
      ''
      
        'ESTADOS: Para crear un estado haga click sobre el bot�n de estad' +
        'os en la barra de herramientas (bot�n con un circulo). Cada vez '
      
        'que haga click sobre la zona de dibujo, se a�adir� un estado. Pa' +
        'ra eliminar un estado, seleccionelo con el bot�n izquierdo del r' +
        'aton, '
      'y haga click con el boton derecho.'
      ''
      
        'TRANSICIONES: Haga click sobre el bot�n de transiciones en la ba' +
        'rra de herramientas (bot�n con una flecha larga). Hecho esto, '
      
        'haga click una vez sobre el estado origen y despu�s sobre el est' +
        'ado final. Para mover una transici�n, arrastre el triangulo negr' +
        'o que '
      
        'aparece sobre la transici�n (notese que es posible que este tria' +
        'ngulo quede oculto '#39'debajo'#39' de un estado; mueva el estado para '
      
        'poder ver el triangulo). Para eliminar una transici�n, seleccion' +
        'ela con el bot�n izquierdo del rat�n, y haga click con el bot�n ' +
        'derecho.'
      ''
      
        'Una vez creados los estados y las transiciones, es necesario eti' +
        'quetarlos. En BOOLE es necesario etiquetar TODOS los estados y '
      
        'transiciones (una transici�n no etiquetada NO se  interpretar� c' +
        'omo una transici�n incondicional). Para etiquetar un estado o un' +
        'a '
      
        'transici�n, haga click sobre el bot�n de selecci�n en la barra d' +
        'e herramientas (bot�n con una flecha peque�a). Despu�s, haga '
      
        'doble click sobre el estado o transici�n que desea etiquetar y s' +
        'e le pedir�n los valores de la etiqueta.')
    ParentFont = False
    ReadOnly = True
    TabOrder = 3
  end
  object Memo4: TMemo
    Left = 24
    Top = 8
    Width = 625
    Height = 33
    BorderStyle = bsNone
    Lines.Strings = (
      
        'Para crear un nuevo automata vaya al men� Archivo -> Nuevo. Sele' +
        'ccione el tipo de automata (Moore o Mealy) y el numero de '
      'se�ales de entrada y salida.')
    ReadOnly = True
    TabOrder = 4
  end
  object Memo5: TMemo
    Left = 24
    Top = 416
    Width = 537
    Height = 81
    BorderStyle = bsNone
    Lines.Strings = (
      'Una vez creado el automata, puede hacer lo siguiente:'
      
        '     (*) Ver el circuito correspondiente con flip-flops JK o D (' +
        'men� Ver Circuito)'
      
        '     (*) Ver las tablas y ecuaciones del automata (men� Resultad' +
        'os -> Dise�o)'
      '     (*) Simular el automata (men� Resultados -> Simular)  '
      '     (*) Minimizar el automata (men� Resultados -> Reducci�n)'
      '     (*) Crear un fichero PLD (men� Archivo -> Exportar a PLD)')
    ReadOnly = True
    TabOrder = 5
  end
end
