object fKarnaugh: TfKarnaugh
  Left = 260
  Top = 137
  BorderStyle = bsSingle
  Caption = 'Veitch-Karnaugh'
  ClientHeight = 393
  ClientWidth = 502
  Color = clBtnFace
  Constraints.MinHeight = 420
  Constraints.MinWidth = 510
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnPaint = FormPaint
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 334
    Align = alLeft
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 183
      Height = 332
      Align = alClient
      Caption = 'Opciones'
      TabOrder = 0
      object tipoVK: TRadioGroup
        Left = 2
        Top = 129
        Width = 179
        Height = 73
        Align = alTop
        Caption = 'Tipo Diagrama'
        ItemIndex = 0
        Items.Strings = (
          'V-K 1'
          'V-K 2')
        TabOrder = 0
        OnClick = tipoVKClick
      end
      object tipoVisu: TRadioGroup
        Left = 2
        Top = 202
        Width = 179
        Height = 65
        Align = alTop
        Caption = 'Mostrar variables:'
        ItemIndex = 0
        Items.Strings = (
          'Binario'
          'Lineas')
        TabOrder = 1
        OnClick = tipoVisuClick
      end
      object pMostrarLazos: TPanel
        Left = 2
        Top = 15
        Width = 179
        Height = 41
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 2
        object ckMostrarLazos: TCheckBox
          Left = 12
          Top = 11
          Width = 97
          Height = 17
          Caption = 'Mostrar lazos'
          TabOrder = 0
          OnClick = ckMostrarLazosClick
        end
      end
      object grpCompletar: TGroupBox
        Left = 2
        Top = 56
        Width = 179
        Height = 73
        Align = alTop
        Caption = 'Completar con:'
        TabOrder = 3
        object Button1: TButton
          Left = 16
          Top = 16
          Width = 33
          Height = 25
          Caption = '0'
          TabOrder = 0
          OnClick = Button1Click
        end
        object Button3: TButton
          Left = 72
          Top = 16
          Width = 33
          Height = 25
          Caption = '1'
          TabOrder = 1
          OnClick = Button3Click
        end
        object Button4: TButton
          Left = 128
          Top = 16
          Width = 33
          Height = 25
          Caption = 'X'
          TabOrder = 2
          OnClick = Button4Click
        end
        object Button9: TButton
          Left = 51
          Top = 48
          Width = 75
          Height = 17
          Caption = 'Borrar Todo'
          TabOrder = 3
          OnClick = Button9Click
        end
      end
      object Panel3: TPanel
        Left = 2
        Top = 267
        Width = 179
        Height = 63
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 4
        object gbSalida: TGroupBox
          Left = 0
          Top = 0
          Width = 48
          Height = 63
          Align = alClient
          Caption = 'Salida:'
          TabOrder = 0
          object listVarSal: TListBox
            Left = 2
            Top = 15
            Width = 44
            Height = 46
            Align = alClient
            ItemHeight = 13
            TabOrder = 0
            OnClick = listVarSalClick
          end
        end
        object gbLazos: TGroupBox
          Left = 48
          Top = 0
          Width = 131
          Height = 63
          Align = alRight
          Caption = 'Lazos'
          TabOrder = 1
          object listLazos: TListBox
            Left = 2
            Top = 15
            Width = 127
            Height = 46
            Align = alClient
            ItemHeight = 13
            TabOrder = 0
            OnClick = listLazosClick
          end
        end
      end
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 334
    Width = 502
    Height = 59
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object bAceptar: TButton
      Left = 398
      Top = 16
      Width = 75
      Height = 25
      Caption = 'Aceptar'
      TabOrder = 0
      OnClick = bAceptarClick
    end
    object Button2: TButton
      Left = 30
      Top = 16
      Width = 123
      Height = 25
      Caption = 'Copiar al Portapapeles'
      TabOrder = 1
      OnClick = Button2Click
    end
    object bCancelar: TButton
      Left = 288
      Top = 16
      Width = 75
      Height = 25
      Caption = 'Cancelar'
      TabOrder = 2
      OnClick = bCancelarClick
    end
  end
  object Panel4: TPanel
    Left = 185
    Top = 0
    Width = 317
    Height = 334
    Align = alClient
    TabOrder = 2
    object Mapa: TKarnaugh
      Left = 1
      Top = 1
      Width = 315
      Height = 210
      Align = alClient
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      OnMouseDown = MapaMouseDown
      OnPaint = MapaPaint
    end
    object gbExprBool: TGroupBox
      Left = 1
      Top = 272
      Width = 315
      Height = 61
      Align = alBottom
      Caption = 'Expresi'#243'n Booleana'
      TabOrder = 0
      object edExprBool: TEdit
        Left = 8
        Top = 24
        Width = 201
        Height = 21
        TabOrder = 0
      end
      object Button5: TButton
        Left = 216
        Top = 24
        Width = 75
        Height = 25
        Caption = 'Evaluar'
        TabOrder = 1
        OnClick = Button5Click
      end
    end
    object gbDibujarLazos: TGroupBox
      Left = 1
      Top = 211
      Width = 315
      Height = 61
      Align = alBottom
      Caption = 'Dibujar Lazos'
      TabOrder = 1
      object SpeedButton1: TSpeedButton
        Left = 16
        Top = 24
        Width = 23
        Height = 25
        Glyph.Data = {
          DE010000424DDE01000000000000760000002800000024000000120000000100
          0400000000006801000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333336633
          3333333333333FF3333333330000333333364463333333333333388F33333333
          00003333333E66433333333333338F38F3333333000033333333E66333333333
          33338FF8F3333333000033333333333333333333333338833333333300003333
          3333446333333333333333FF3333333300003333333666433333333333333888
          F333333300003333333E66433333333333338F38F333333300003333333E6664
          3333333333338F38F3333333000033333333E6664333333333338F338F333333
          0000333333333E6664333333333338F338F3333300003333344333E666433333
          333F338F338F3333000033336664333E664333333388F338F338F33300003333
          E66644466643333338F38FFF8338F333000033333E6666666663333338F33888
          3338F3330000333333EE666666333333338FF33333383333000033333333EEEE
          E333333333388FFFFF8333330000333333333333333333333333388888333333
          0000}
        NumGlyphs = 2
        OnClick = SpeedButton1Click
      end
      object Button7: TButton
        Left = 224
        Top = 24
        Width = 65
        Height = 25
        Caption = 'Evaluar'
        TabOrder = 0
        OnClick = Button7Click
      end
      object Button6: TButton
        Left = 136
        Top = 24
        Width = 73
        Height = 25
        Caption = 'Borrar Lazos'
        TabOrder = 1
        OnClick = Button6Click
      end
      object Button8: TButton
        Left = 56
        Top = 24
        Width = 65
        Height = 25
        Caption = 'Crear Lazo'
        TabOrder = 2
        OnClick = Button8Click
      end
    end
  end
end
