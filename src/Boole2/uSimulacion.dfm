object fSimulacion: TfSimulacion
  Left = 226
  Top = 186
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Simulaci'#243'n Batch'
  ClientHeight = 349
  ClientWidth = 503
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 503
    Height = 349
    Align = alClient
    TabOrder = 0
    object gridSimulacion: TStringGrid
      Left = 39
      Top = 57
      Width = 425
      Height = 201
      ColCount = 14
      DefaultColWidth = 35
      DefaultRowHeight = 18
      FixedCols = 0
      RowCount = 15
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Pitch = fpFixed
      Font.Style = []
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
      ParentFont = False
      PopupMenu = PopupTabla
      TabOrder = 0
      OnMouseDown = gridSimulacionMouseDown
      OnMouseMove = gridSimulacionMouseMove
      OnSelectCell = gridSimulacionSelectCell
    end
    object Panel2: TPanel
      Left = 84
      Top = 272
      Width = 337
      Height = 65
      BevelOuter = bvNone
      TabOrder = 1
      object btIniciarSim: TBitBtn
        Left = 0
        Top = 0
        Width = 121
        Height = 25
        Caption = 'Iniciar Simulaci'#243'n'
        TabOrder = 0
        OnClick = btIniciarSimClick
        Glyph.Data = {
          7E000000424D7E000000000000003E0000002800000010000000100000000100
          010000000000400000000000000000000000020000000200000000000000FFFF
          FF00FFFF0000FFFF0000EFFF0000E3FF0000E0FF0000E03F0000E00F0000E003
          0000E0070000E01F0000E07F0000E1FF0000E7FF0000FFFF0000FFFF0000FFFF
          0000}
      end
      object btPausarSim: TBitBtn
        Left = 40
        Top = 40
        Width = 121
        Height = 25
        Caption = 'Pausar Simulaci'#243'n'
        Enabled = False
        TabOrder = 1
        OnClick = btPausarSimClick
        Glyph.Data = {
          7E000000424D7E000000000000003E0000002800000010000000100000000100
          010000000000400000000000000000000000020000000200000000000000FFFF
          FF00FFFF0000FFFF0000FFFF0000FFFF0000F18F0000F18F0000F18F0000F18F
          0000F18F0000F18F0000F18F0000F18F0000FFFF0000FFFF0000FFFF0000FFFF
          0000}
      end
      object btSiguiente: TBitBtn
        Left = 136
        Top = 0
        Width = 75
        Height = 25
        Caption = 'Siguiente'
        Enabled = False
        TabOrder = 2
        OnClick = btSiguienteClick
        Glyph.Data = {
          7E000000424D7E000000000000003E0000002800000010000000100000000100
          010000000000400000000000000000000000020000000200000000000000FFFF
          FF00FFFF0000FFFF0000DFE30000C7E30000C1E30000C0630000C0030000C003
          0000C0030000C0230000C0E30000C3E30000CFE30000FFE30000FFFF0000FFFF
          0000}
      end
      object btPararSim: TBitBtn
        Left = 176
        Top = 40
        Width = 121
        Height = 25
        Caption = 'Borrar Tabla'
        TabOrder = 3
        OnClick = btPararSimClick
        Glyph.Data = {
          7E000000424D7E000000000000003E0000002800000010000000100000000100
          010000000000400000000000000000000000020000000200000000000000FFFF
          FF00FFFF0000FFFF0000FFFF0000FFFF0000F00F0000F00F0000F00F0000F00F
          0000F00F0000F00F0000F00F0000F00F0000FFFF0000FFFF0000FFFF0000FFFF
          0000}
      end
      object btRapido: TBitBtn
        Left = 224
        Top = 0
        Width = 113
        Height = 25
        Caption = 'Proceso R'#225'pido'
        Enabled = False
        TabOrder = 4
        OnClick = btRapidoClick
        Glyph.Data = {
          7E000000424D7E000000000000003E0000002800000010000000100000000100
          010000000000400000000000000000000000020000000200000000000000FFFF
          FF00FFFF0000FFFF0000FFFF0000BEFF00008E3F0000820F0000800700008001
          000080070000861F00009E7F0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
          0000}
      end
    end
    object Panel3: TPanel
      Left = 64
      Top = 16
      Width = 377
      Height = 33
      BevelOuter = bvNone
      TabOrder = 2
      object Label1: TLabel
        Left = 4
        Top = 11
        Width = 66
        Height = 13
        Caption = 'Estado Inicial:'
      end
      object Label2: TLabel
        Left = 244
        Top = 11
        Width = 79
        Height = 13
        Caption = 'Numero de Filas:'
      end
      object comboInicial: TComboBox
        Left = 76
        Top = 7
        Width = 145
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 0
        OnChange = comboInicialChange
      end
      object spinFilas: TCSpinEdit
        Left = 332
        Top = 6
        Width = 41
        Height = 22
        EditorEnabled = False
        MaxValue = 64
        MinValue = 3
        TabOrder = 1
        Value = 3
        OnChange = spinFilasChange
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 432
    Top = 65520
    object Log1: TMenuItem
      Caption = '&Log'
      object VerLog1: TMenuItem
        Caption = '&Ver Log'
        OnClick = VerLog1Click
      end
    end
    object Ayuda1: TMenuItem
      Caption = '&Ayuda'
      OnClick = Ayuda1Click
    end
    object Cerrar1: TMenuItem
      Caption = 'Cerrar'
      OnClick = Cerrar1Click
    end
  end
  object PopupTabla: TPopupMenu
    OnPopup = PopupTablaPopup
    Left = 24
    Top = 16
    object menuInsertarfila: TMenuItem
      Caption = 'Insertar fila'
      OnClick = menuInsertarfilaClick
    end
    object menuEliminarfila: TMenuItem
      Caption = 'Eliminar fila'
      OnClick = menuEliminarfilaClick
    end
  end
end
