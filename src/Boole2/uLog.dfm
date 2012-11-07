object fLog: TfLog
  Left = 289
  Top = 259
  Width = 700
  Height = 418
  Caption = 'Log de Simulaci'#243'n'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object memoLog: TMemo
    Left = 0
    Top = 0
    Width = 692
    Height = 351
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier'
    Font.Pitch = fpFixed
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
    WordWrap = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 351
    Width = 692
    Height = 40
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object Button1: TButton
      Left = 276
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Imprimir...'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 392
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Guardar...'
      TabOrder = 1
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 507
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Cerrar'
      TabOrder = 2
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 109
      Top = 8
      Width = 129
      Height = 25
      Caption = 'Copiar al Portapapeles'
      TabOrder = 3
      OnClick = Button4Click
    end
  end
  object saveLog: TSaveDialog
    DefaultExt = 'log'
    Filter = 'Log de Simulacion|*.log|Fichero de Texto|*.txt|Todos|*.*'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofShowHelp, ofEnableSizing]
    Left = 640
    Top = 32
  end
  object printLog: TPrintDialog
    Options = [poPrintToFile, poWarning, poHelp]
    Left = 640
    Top = 80
  end
end
