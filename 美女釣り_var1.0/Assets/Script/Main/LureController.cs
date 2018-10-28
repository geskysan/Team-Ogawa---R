﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LureController : MonoBehaviour {

    [SerializeField] GameObject m_lureObj;

    // タップ座標
    private Vector2 m_tapPos;

    // Use this for initialization
    void Start () {

	}
	
	// Update is called once per frame
	void Update () {
        Tap();
    }


    // タップした位置に移動
    void Tap()
    {
        if(Input.GetMouseButtonDown(0))
        {
            // 非表示状態なら表示
            if(m_lureObj.activeSelf == false)
            {
                m_lureObj.SetActive(true);
            }

            // タップした位置
            m_tapPos = new Vector2(Input.mousePosition.x, Input.mousePosition.y);

            // Lureの位置をクリック地点に移動
            m_lureObj.transform.localPosition = new Vector3(m_tapPos.x - (Screen.width / 2), m_tapPos.y - (Screen.height / 2), 0f);
        }
    }
}