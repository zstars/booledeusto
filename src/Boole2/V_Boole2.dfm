object Form1Boole2: TForm1Boole2
  Left = 793
  Top = 192
  Width = 785
  Height = 538
  HorzScrollBar.Tracking = True
  VertScrollBar.Tracking = True
  Caption = 'Sin Titulo (Moore).'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = True
  Position = poScreenCenter
  Scaled = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 16
  object Splitter1: TSplitter
    Left = 0
    Top = 361
    Width = 769
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    Beveled = True
  end
  object BarraEstado: TStatusBar
    Left = 0
    Top = 454
    Width = 769
    Height = 26
    DragCursor = crDefault
    Panels = <>
    SimplePanel = False
    SizeGrip = False
  end
  object TableroBox: TScrollBox
    Left = 161
    Top = 0
    Width = 608
    Height = 361
    Align = alClient
    TabOrder = 1
    object Tablero: TImage
      Left = -8
      Top = -8
      Width = 1024
      Height = 768
      ParentShowHint = False
      ShowHint = False
      Stretch = True
      Visible = False
      OnDblClick = TableroDblClick
      OnMouseDown = TableroMouseDown
      OnMouseMove = TableroMouseMove
      OnMouseUp = TableroMouseUp
    end
  end
  object pTextAsoc: TPanel
    Left = 0
    Top = 364
    Width = 769
    Height = 90
    Align = alBottom
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 2
    Visible = False
    object txAsociado: TMemo
      Left = 1
      Top = 1
      Width = 767
      Height = 88
      Align = alClient
      TabOrder = 0
    end
  end
  object pSimulacion: TPanel
    Left = 0
    Top = 0
    Width = 161
    Height = 361
    Align = alLeft
    TabOrder = 3
    Visible = False
    object Label1: TLabel
      Left = 8
      Top = 8
      Width = 80
      Height = 16
      Caption = 'Estado Inicial'
    end
    object Button1: TButton
      Left = 96
      Top = 352
      Width = 49
      Height = 17
      Caption = 'Cerrar'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = Button1Click
    end
    object comboInicial: TComboBox
      Left = 8
      Top = 24
      Width = 145
      Height = 24
      Style = csDropDownList
      ItemHeight = 16
      TabOrder = 1
      OnChange = comboInicialChange
    end
    object Button2: TButton
      Left = 88
      Top = 192
      Width = 60
      Height = 40
      Caption = 'CLK'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = Button2Click
    end
    object btReset: TButton
      Left = 11
      Top = 200
      Width = 59
      Height = 17
      Caption = 'RESET'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = btResetClick
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 232
      Width = 145
      Height = 113
      Caption = 'Salida'
      TabOrder = 5
      object Label2: TLabel
        Left = 24
        Top = 64
        Width = 86
        Height = 16
        Caption = 'Estado Actual:'
      end
      object gridVarsSal: TStringGrid
        Left = 4
        Top = 16
        Width = 137
        Height = 42
        DefaultColWidth = 25
        DefaultRowHeight = 18
        FixedCols = 0
        RowCount = 2
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = 'Courier'
        Font.Style = []
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
        ParentFont = False
        ScrollBars = ssNone
        TabOrder = 0
        ColWidths = (
          25
          25
          25
          25
          25)
      end
      object edEstadoActual: TEdit
        Left = 12
        Top = 81
        Width = 121
        Height = 24
        ReadOnly = True
        TabOrder = 1
      end
    end
    object Button4: TButton
      Left = 16
      Top = 352
      Width = 65
      Height = 17
      Caption = 'Ver Log...'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      OnClick = Button4Click
    end
    object GroupBox1: TGroupBox
      Left = 8
      Top = 56
      Width = 145
      Height = 129
      Caption = 'Entrada'
      TabOrder = 2
      object gridVarsEnt: TStringGrid
        Left = 4
        Top = 16
        Width = 137
        Height = 42
        DefaultColWidth = 25
        DefaultRowHeight = 18
        FixedCols = 0
        RowCount = 2
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = 'Courier'
        Font.Style = []
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
        ParentFont = False
        ScrollBars = ssNone
        TabOrder = 0
        OnMouseDown = gridVarsEntMouseDown
        ColWidths = (
          25
          25
          25
          25
          25)
      end
      object btAplicar: TBitBtn
        Left = 28
        Top = 64
        Width = 89
        Height = 25
        Caption = 'Aplicar'
        Default = True
        ModalResult = 6
        TabOrder = 1
        OnClick = btAplicarClick
        Glyph.Data = {
          06030000424D06030000000000003600000028000000100000000F0000000100
          180000000000D002000000000000000000000000000000000000FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000000FFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000C00000
          C00000C00000C000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFF00000000C00000C00000C00000C00000C00000C000000000FFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF11111100C00000C00000C00000
          C00000C00000C00000C00000C000111111FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          00000000C00000C00000C00000C00000C00000C00000C00000C00000C00000C0
          00000000FFFFFFFFFFFFFFFFFF00000000C00000C00000C00000C00000C00000
          C00000C00000C00000C00000C00000C00000C000000000FFFFFF00000000C000
          00C00000C00000000000000000C00000C00000C00000C00000000000000000C0
          0000C00000C000000000FFFFFF000000000000000000FFFFFF00000000C00000
          C00000C00000C000000000FFFFFF000000000000000000FFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFF00000000C00000C00000C00000C000000000FFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000C00000
          C00000C00000C000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFF00000000C00000C00000C00000C000000000FFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000C00000
          C00000C00000C000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFF00000000C00000C00000C00000C000000000FFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000C00000
          C00000C00000C000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFF000000000000000000000000000000000000FFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFF}
      end
      object edEntrada: TEdit
        Left = 12
        Top = 96
        Width = 121
        Height = 24
        ReadOnly = True
        TabOrder = 2
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 672
    Top = 96
    object Archivo1: TMenuItem
      Caption = '&Archivo'
      OnClick = Archivo1Click
      object Nuevo1: TMenuItem
        Caption = '&Nuevo'
        OnClick = Nuevo1Click
      end
      object Cargar1: TMenuItem
        Caption = '&Abrir'
        OnClick = Cargar1Click
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object Salvar1: TMenuItem
        Caption = '&Guardar'
        OnClick = Salvar1Click
      end
      object Guardar1: TMenuItem
        Caption = 'G&uardar  como...'
        OnClick = Guardar1Click
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object StartWeblabFPGAI: TMenuItem
        Caption = 'Start Weblab &FPGA'
        OnClick = StartWeblabFPGAIClick
      end
      object N11: TMenuItem
        Caption = '-'
      end
      object ExportToWeblabInternal: TMenuItem
        Caption = 'Export to Weblab VHDL (&Internal Clock)'
        OnClick = ExportToWeblabInternalClick
      end
      object ExportToWeblabWeblab: TMenuItem
        Caption = 'Export to Weblab VHDL (&Weblab Clock)'
        OnClick = ExportToWeblabWeblabClick
      end
      object ExportToWeblabSwitch: TMenuItem
        Caption = 'Export to Weblab VHDL (&Switch Clock)'
        OnClick = ExportToWeblabSwitchClick
      end
      object ExportToWeblabButton: TMenuItem
        Caption = 'Export to Weblab VHDL (&Button Clock)'
        OnClick = ExportToWeblabButtonClick
      end
      object N12: TMenuItem
        Caption = '-'
      end
      object ExportaraVHDL1: TMenuItem
        Caption = 'Exportar a &VHDL'
        OnClick = ExportaraVHDL1Click
      end
      object ExportaraPDL1: TMenuItem
        Caption = 'Exportar a &OrCAD-PLD'
        OnClick = ExportaraPDL1Click
      end
      object ExportaraJEDEC1: TMenuItem
        Caption = 'Exportar a &JEDEC'
        OnClick = ExportaraJEDEC1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Imprimir1: TMenuItem
        Caption = '&Imprimir'
        OnClick = Imprimir1Click
      end
      object N6: TMenuItem
        Caption = '-'
      end
      object Salir1: TMenuItem
        Caption = '&Salir'
        OnClick = Salir1Click
      end
    end
    object Edicin1: TMenuItem
      Caption = 'Edici'#243'n'
      OnClick = Edicin1Click
      object CopiarAutomata: TMenuItem
        Caption = 'Copiar Autom'#225'ta al Portapapeles'
        ShortCut = 16451
        OnClick = CopiarAutomataClick
      end
      object CopiarTablas: TMenuItem
        Caption = 'Copiar Tablas al Portapapeles'
        OnClick = CopiarTablasClick
      end
    end
    object Circuito1: TMenuItem
      Caption = 'Ver &Circuito'
      OnClick = Circuito1Click
      object ConflipflopsJK1: TMenuItem
        Caption = 'Con flip-flops &JK'
        OnClick = ConflipflopsJK1Click
      end
      object ConflipflopsD1: TMenuItem
        Caption = 'Con flip-flops &D'
        OnClick = ConflipflopsD1Click
      end
    end
    object Resultados1: TMenuItem
      Caption = '&Resultados'
      OnClick = Resultados1Click
      object VerificarCompletitud: TMenuItem
        Caption = #191'Es determinista?'
        OnClick = VerificarCompletitudClick
      end
      object Verificar: TMenuItem
        Caption = #191'Es correcto?'
        OnClick = VerificarClick
      end
      object N10: TMenuItem
        Caption = '-'
      end
      object Equivalente: TMenuItem
        Caption = 'Obtener Mealy Equivalente'
        OnClick = EquivalenteClick
      end
      object Contraer1: TMenuItem
        Caption = 'Contraer'
        Visible = False
        OnClick = Contraer1Click
      end
      object Expandir1: TMenuItem
        Caption = 'Expandir'
        Visible = False
        OnClick = Expandir1Click
      end
      object N9: TMenuItem
        Caption = '-'
      end
      object InteractivaRapida: TMenuItem
        Caption = '&Simulaci'#243'n Interactiva'
        OnClick = InteractivaRapidaClick
      end
      object Simulacion: TMenuItem
        Caption = 'Simulaci'#243'n Interactiva Detallada'
        OnClick = SimulacionClick
      end
      object BatchRapida: TMenuItem
        Caption = 'Simulaci'#243'n &Batch'
        OnClick = BatchRapidaClick
      end
      object Batch: TMenuItem
        Caption = 'Simulaci'#243'n Batch Detallada'
        OnClick = BatchClick
      end
      object N7: TMenuItem
        Caption = '-'
      end
      object Reduccion: TMenuItem
        Caption = '&Minimizaci'#243'n de Estados'
        OnClick = ReduccionClick
      end
      object N8: TMenuItem
        Caption = '-'
      end
      object Tablas1: TMenuItem
        Caption = '&Dise'#241'o del Aut'#243'mata'
        OnClick = Tablas1Click
      end
    end
    object Ver1: TMenuItem
      Caption = '&Ver'
      OnClick = Ver1Click
      object BarradeBotones1: TMenuItem
        Caption = '&Barra de Herramientas'
        Checked = True
        OnClick = BarradeBotones1Click
      end
      object mnTextoAsociado: TMenuItem
        Caption = 'Texto Asociado'
        OnClick = mnTextoAsociadoClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object CodigoVHDL1: TMenuItem
        Caption = 'C'#243'digo &VHDL'
        OnClick = CodigoVHDL1Click
      end
      object CodigoPDL1: TMenuItem
        Caption = 'C'#243'digo OrCAD-&PLD'
        OnClick = CodigoPDL1Click
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object General1: TMenuItem
        Caption = '&Configuracion'
        OnClick = General1Click
      end
    end
    object Ayuda1: TMenuItem
      Caption = 'A&yuda'
      OnClick = Ayuda1Click
      object GeneralHelp1: TMenuItem
        Caption = 'General Help'
        OnClick = GeneralHelp1Click
      end
      object WeblabHelp1: TMenuItem
        Caption = 'Weblab Help'
        OnClick = WeblabHelp1Click
      end
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '.aut'
    Filter = 'Ficheros de Automata|*.aut'
    Left = 672
    Top = 72
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '.aut'
    Filter = 'Ficheros de Automata|*.aut'
    Left = 672
    Top = 48
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 672
    Top = 24
  end
  object SaveDialog2: TSaveDialog
    DefaultExt = '.aut'
    Filter = 'Ficheros PLD|*.pld'
    Left = 672
  end
  object TimerParpadeoEstado: TTimer
    Enabled = False
    Interval = 100
    OnTimer = TimerParpadeoEstadoTimer
    Left = 675
    Top = 130
  end
  object MainMenu2: TMainMenu
    Left = 376
    Top = 256
  end
  object MainMenu3: TMainMenu
    Left = 376
    Top = 256
  end
end
