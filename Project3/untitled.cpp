    int i,j;
    for(i = 0; i < VIEW_WIDTH; i++){
        for(j = 0; j < VIEW_HEIGHT; j++){
            vector<Actor*>::iterator it = m_vec[i][j].begin();
            while(it != m_vec[i][j].end()){
                m_vec[i][j].erase(it);
            }
            m_vec[i][j].clear();
        }
    }
    