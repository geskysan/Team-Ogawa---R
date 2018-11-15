using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using DG.Tweening;

using MySql.Data;
using MySql.Data.MySqlClient;

public class TitleControler : MonoBehaviour
{

    [SerializeField]
    CanvasGroup m_tapLogo; //ロゴ
    [SerializeField]
    CanvasGroup m_titleLogo; //タイトルロゴ
    [SerializeField]
    GameObject NewPlayer; //そんまんま

    [SerializeField] float m_scaleSize = 1.2f;
    [SerializeField] float m_scaleTime;
    [SerializeField] float m_titleFadeTime;

    [SerializeField] private float DurationSeconds;
    [SerializeField] private Ease EaseType;

    [SerializeField]
    InputField inputField;

    string SERVER = "153.126.208.136"; //さくらVPSに接続してる
    string DATABASE = "bjo";
    string USERID = "player";
    string PORT = "3306";
    string PASSWORD = "Player_1";

    string username;
    object userid;
    // string TABLENAME = "user";

    // Use this for initialization
    void Start()
    {
        //タイトルの動き
        Sequence seq = DOTween.Sequence()
            .OnStart(() =>
            {
                m_titleLogo.GetComponent<GameObject>();
                m_titleLogo.transform.localScale = new Vector3(0.1f, 0.1f, 0.1f);

            })
        .Append(m_titleLogo.transform.DOScale(1.0f, m_scaleTime))
        .Join(m_titleLogo.DOFade(1.0f, m_titleFadeTime))
        .Append(m_titleLogo.transform.DOScale(0.9f, 0.5f))
        .Join(m_titleLogo.transform.DORotate(new Vector3(0.0f, 0.0f, -10.0f), 1.5f))
        .OnComplete(() =>
        {
            m_titleLogo.transform.DORotate(new Vector3(0.0f, 0.0f, 10.0f), 1.5f).SetLoops(-1, LoopType.Yoyo);

        });

        SoundScript.Instance.PlayBGM(SoundNameData.BGM_TITLE);
        m_tapLogo.DOFade(0.5f, this.DurationSeconds).SetEase(this.EaseType).SetLoops(-1, LoopType.Yoyo);

        string connCmd =
                  "server=" + SERVER + ";" +
                  "database=" + DATABASE + ";" +
                  "userid=" + USERID + ";" +
                  "port=" + PORT + ";" +
                  "password=" + PASSWORD;

        MySqlConnection conn = new MySqlConnection(connCmd);
        //ここUSERIDを取ってる
        try
        {
            Debug.Log("MySQLと接続中...");
            conn.Open();

            string sql = "SELECT MAX( userid ) FROM user;";
            MySqlCommand cmd = new MySqlCommand(sql, conn);
            MySqlDataReader rdr = cmd.ExecuteReader();

            while (rdr.Read())
            {
                userid = rdr[0];
                Debug.Log(rdr[0]);

            }
            rdr.Close();

        }
        catch (Exception ex)
        {
            Debug.Log(ex.ToString());
        }
        conn.Close();
        Debug.Log("接続を終了しました");

    }



    // Update is called once per frame
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            if (!PlayerPrefs.HasKey("Init"))
            {
                NewPlayer.gameObject.SetActive(true);
            }
            if (PlayerPrefs.HasKey("Init"))
            {
                SceneNavigator.Instance.Change("menu");
            }
        }
    }

    //ユーザー作るときの奴
    public void Decision()
    {
        int userid_mysql = (int)userid;
        Debug.Log(userid_mysql);
        string connCmd =
                "server=" + SERVER + ";" +
                "database=" + DATABASE + ";" +
                "userid=" + USERID + ";" +
                "port=" + PORT + ";" +
                "password=" + PASSWORD;

        MySqlConnection conn = new MySqlConnection(connCmd);

        try
        {
            Debug.Log("MySQLと接続中...");
            conn.Open();

            string sql = "INSERT INTO user (userid,username,highscore) values (" + userid_mysql + "+1," + "'" + username + "'" + ",0);";
            MySqlCommand cmd = new MySqlCommand(sql, conn);
            Debug.Log(sql);
            cmd.ExecuteNonQuery();
        }
        catch (Exception ex)
        {
            Debug.Log(ex.ToString());
        }
        conn.Close();

        PlayerPrefs.SetInt("Init", 1); // ”Init”のキーをint型の値(1)で保存
        PlayerPrefs.SetInt("user_id", userid_mysql + 1);

        Debug.Log("接続を終了しました");
    }
    //名前入力
    public void FieldInput()
    {
        username = inputField.text;
        Debug.Log(username);
    }
}

