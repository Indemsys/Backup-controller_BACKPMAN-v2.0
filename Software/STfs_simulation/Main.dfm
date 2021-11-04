object frm_Main: Tfrm_Main
  Left = 0
  Top = 0
  Caption = 'STFS simulator'
  ClientHeight = 1082
  ClientWidth = 1250
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poScreenCenter
  PixelsPerInch = 96
  DesignSize = (
    1250
    1082)
  TextHeight = 15
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 110
    Height = 15
    Caption = 'Number of iterations'
  end
  object btn_Start_Simulation: TButton
    Left = 9
    Top = 1024
    Width = 100
    Height = 33
    Anchors = [akLeft, akBottom]
    Caption = 'Start'
    TabOrder = 0
    OnClick = btn_Start_SimulationClick
  end
  object PageControl: TPageControl
    Left = 115
    Top = 0
    Width = 1135
    Height = 1063
    ActivePage = tsView
    Align = alRight
    MultiLine = True
    TabOrder = 1
    TabPosition = tpLeft
    ExplicitLeft = 128
    ExplicitHeight = 1062
    object tsLog: TTabSheet
      Caption = 'Log'
      object Log_memo: TMemo
        Left = 0
        Top = 0
        Width = 1104
        Height = 1055
        Align = alClient
        ScrollBars = ssBoth
        TabOrder = 0
        ExplicitHeight = 1054
      end
    end
    object tsView: TTabSheet
      Caption = 'View'
      ImageIndex = 1
      object ViewPanel: TPanel
        Left = 0
        Top = 0
        Width = 1104
        Height = 1055
        Margins.Left = 0
        Margins.Top = 0
        Margins.Right = 0
        Margins.Bottom = 0
        Align = alClient
        BevelEdges = []
        BevelOuter = bvNone
        Color = clBtnText
        FullRepaint = False
        ParentBackground = False
        TabOrder = 0
        ExplicitHeight = 1054
      end
    end
  end
  object ed_Iterations_number: TMaskEdit
    Left = 8
    Top = 29
    Width = 73
    Height = 23
    TabOrder = 2
    Text = '200'
  end
  object CmdsPanel: TPanel
    Left = 8
    Top = 886
    Width = 102
    Height = 129
    BevelOuter = bvLowered
    TabOrder = 3
    object btn_SectorDump: TButton
      Left = 1
      Top = 24
      Width = 100
      Height = 33
      Align = alTop
      Caption = 'Sector dump'
      TabOrder = 0
      OnClick = btn_SectorDumpClick
      ExplicitLeft = 5
      ExplicitTop = 39
      ExplicitWidth = 105
    end
    object cb_Sector: TComboBox
      Left = 1
      Top = 1
      Width = 100
      Height = 23
      Align = alTop
      ItemIndex = 0
      TabOrder = 1
      Text = '0'
      Items.Strings = (
        '0'
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7')
    end
    object btn_CheckSTfs: TButton
      Left = 1
      Top = 57
      Width = 100
      Height = 33
      Align = alTop
      Caption = 'Check STfs'
      TabOrder = 2
      OnClick = btn_CheckSTfsClick
      ExplicitTop = 63
      ExplicitWidth = 105
    end
    object btn_InitSTFS: TButton
      Left = 1
      Top = 90
      Width = 100
      Height = 33
      Align = alTop
      Caption = 'Init STfs'
      TabOrder = 3
      OnClick = btn_InitSTFSClick
    end
  end
  object Sbar: TStatusBar
    Left = 0
    Top = 1063
    Width = 1250
    Height = 19
    Panels = <
      item
        Width = 800
      end>
    ExplicitTop = 1065
  end
  object cb_Fragmented: TCheckBox
    Left = 8
    Top = 66
    Width = 89
    Height = 39
    Caption = 'Enable fragmented write'
    TabOrder = 5
    WordWrap = True
  end
  object Timer: TTimer
    Enabled = False
    Interval = 1
    OnTimer = TimerTimer
    Left = 267
    Top = 596
  end
end
